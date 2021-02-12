/*********************************************************************************
** MIT License
**
** Copyright (c) 2021 VIKAS AWADHIYA
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:

** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.

** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
*********************************************************************************/

#include "lcs.hpp"
#include <vector>

namespace  {

std::string parseTable(const std::vector<std::vector<std::string::size_type>>& table, const std::string& sequence2){

    std::string subSeq(table.back().back(), ' ');
    std::string::reverse_iterator sIt = subSeq.rbegin();

    std::string::size_type rowIndex = table.size() - 1;
    std::string::size_type colIndex = table.front().size() - 1;

    while(rowIndex > 0){

        if(table[rowIndex - 1][colIndex] < table[rowIndex][colIndex] &&
                table[rowIndex][colIndex - 1] < table[rowIndex][colIndex]){

            *sIt = sequence2[rowIndex - 1];
            ++sIt;

            --rowIndex;
            --colIndex;
        }
        else{
            if(table[rowIndex][colIndex] == table[rowIndex - 1][colIndex]){

                --rowIndex;
            }
            else{
                --colIndex;
            }
        }
    }

    return subSeq;
}

}

std::string lcs::subsequence(const std::string &sequence1, const std::string &sequence2){

    std::vector<std::vector<std::string::size_type>> table(
                sequence2.size() + 1, std::vector<std::string::size_type>(sequence1.size() + 1, 0));

    for(std::string::size_type j = 0, seq2Size = sequence2.size(); j < seq2Size; ++j){

        for(std::string::size_type i = 0, seq1Size = sequence1.size(); i < seq1Size; ++i){

            if(sequence1[i] == sequence2[j]){

                table[j + 1][i + 1] = table[j][i] + 1;
            }
            else{
                table[j + 1][i + 1] = std::max(table[j][i + 1], table[j + 1][i]);
            }
        }
    }

    return parseTable(table, sequence2);
}
