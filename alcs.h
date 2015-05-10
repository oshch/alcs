#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

const long long INF = 1e7 + 7;

void FindCriticalPoints(std::string &first, std::string &second, std::vector < std::vector <bool> > &critical_points)
{
    critical_points.resize(first.size() + 1);
    for (size_t i = 0; i <= first.size(); ++i)
        critical_points[i].assign(first.size() + 1, false);

    std::vector<int> v(first.size() + 1, 0);
    std::vector < std::vector <int> > index_on_horisontal(second.size() + 1, v);
    std::vector < std::vector <int> > index_on_vertical(second.size() + 1, v);

    for (size_t j = 0; j <= first.size(); ++j)
        index_on_horisontal[0][j] = j;
    for (size_t l = 0; l <= second.size(); ++l)
        index_on_vertical[l][0] = 0;

    for (size_t l = 1; l <= second.size(); ++l)
    {
        for (size_t j = 1; j <= first.size(); ++j)
        {
            if (second[l - 1] != first[j - 1])
            {
                index_on_horisontal[l][j] = std::max(index_on_vertical[l][j - 1], index_on_horisontal[l - 1][j]);
                index_on_vertical[l][j] = std::min(index_on_vertical[l][j - 1], index_on_horisontal[l - 1][j]);
            }
            else
            {
                index_on_horisontal[l][j] = index_on_vertical[l][j - 1];
                index_on_vertical[l][j] = index_on_horisontal[l - 1][j];
            }
        }
    }

    for (size_t i = 1; i <= first.size(); ++i)
        critical_points[index_on_horisontal[second.size()][i]][i] = true;

}

void FastLCS(std::string &first, std::string &second, std::vector < std::vector <int> > &result)
{
    std::vector < std::vector <bool> > critical_points;
    FindCriticalPoints(first, second, critical_points);

    result.resize(first.size() + 1);
    for (size_t i = 0; i <= first.size(); ++i)
        result[i].assign(first.size() + 1, 0);

    for (size_t i = 1; i <= first.size(); ++i)
        if (!critical_points[i][i])
            result[i][i] = 1;

    for (size_t i = 2; i <= first.size(); ++i)
    {
        for (size_t j = 0; j <= first.size() - i; ++j)
        {
            if (result[j + 1][i + j - 1] != result[j + 2][i + j])
                result[j + 1][i + j] = std::max(result[j + 1][i + j - 1], result[j + 2][i + j]);
            else
            {
                if (result[j + 2][i + j - 1] == result[j + 2][i + j])
                    result[j + 1][i + j] = result[j + 2][i + j];
                else
                {
                    if (critical_points[j + 1][i + j])
                        result[j + 1][i + j] = result[j + 2][i + j];
                    else
                        result[j + 1][i + j] = result[j + 2][i + j] + 1;
                }
            }
        }
    }
}


void SlowLCS(std::string &first, std::string &second, std::vector < std::vector <int> > &result)
{
    std::vector<int> v(second.size() + 1, 0);
    std::vector < std::vector <int> > lcs(first.size() + 1, v);

    result.resize(first.size() + 1);
    for (size_t i = 0; i <= first.size(); i++)
        result[i].assign(first.size() + 1, 0);

    for (size_t ind = 1; ind <= first.size(); ++ind)
    {
        for (size_t i = ind; i <= first.size(); ++i)
        {
            for (size_t j = 1; j <= second.size(); ++j)
            {
                if (first[i - 1] == second[j - 1])
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                else
                    lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }

        for (size_t i = ind; i <= first.size(); ++i)
            result[ind][i] = lcs[i][second.size()];

        for (size_t i = 0; i <= first.size(); ++i)
            for (size_t j = 0; j <= second.size(); ++j)
                lcs[i][j] = 0;
    }

}
