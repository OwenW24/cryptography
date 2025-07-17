#ifndef ATTACK_HPP
#define ATTACK_HPP
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

bool cmp(std::pair<char, double>& a, 
    std::pair<char, double>& b) {  return a.second > b.second; } 

class Freq{
    private:


        std::string xs = "";
        std::string ys = "";
        std::vector<std::pair<char, double>> frq_abc = {
            {'A', 0.082}, {'B', 0.015}, {'C', 0.028}, {'D', 0.043},
            {'E', 0.127}, {'F', 0.022}, {'G', 0.020}, {'H', 0.061},
            {'I', 0.070}, {'J', 0.0015}, {'K', 0.0077}, {'L', 0.040},
            {'M', 0.024}, {'N', 0.067}, {'O', 0.075}, {'P', 0.019},
            {'Q', 0.00095}, {'R', 0.060}, {'S', 0.063}, {'T', 0.091},
            {'U', 0.028}, {'V', 0.0098}, {'W', 0.024}, {'X', 0.0015},
            {'Y', 0.020}, {'Z', 0.00074}                         
        };
        std::unordered_map<char, double> ys_count;
        std::vector<std::pair<char, double>> frq_ys;
        std::map<char, char> ys_to_xs;
        
        void find_freq(){ // assemble ys_count, and frq_ys
            int n = ys.size();
            for (char y: ys) ys_count[y] ++;
            for (auto y : ys_count) frq_ys.push_back({y.first, y.second / (double) n});
            std::sort(frq_ys.begin(), frq_ys.end(), cmp);
        }

        void map_freq(){  // assemble ys_to_xs
            std::sort(frq_abc.begin(), frq_abc.end(), cmp);
            for(int i = 0; i < 26; i++) ys_to_xs[frq_ys[i].first] = frq_abc[i].first;
        }

        void assembleXs(){
            for(char y: ys){
                if (!isalpha(y)) xs += y;
                else xs += tolower(ys_to_xs[y]);
            }
        }
        
    public:

        Freq(std::string ys){
            this->ys = ys;
            find_freq();
            map_freq();
            assembleXs();
        }
        std::string get_ys(){ return ys; }

        std::string get_xs(){ return xs; }
};

#endif