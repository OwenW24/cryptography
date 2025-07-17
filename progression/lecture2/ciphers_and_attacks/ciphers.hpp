#ifndef CIPHERS_HPP
#define CIPHERS_HPP

#include <iostream>
#include <string>

class Shift{
    private:
        int k = 0;
        std::string xs = "";
        std::string ys = "";

        char enc(char x, int k){
            x = x - 97;  // ascii a == 97, shifts letter to [0..25]
            int shift = (x + k) % 26;
            if (shift < 0) shift += 26;
            return 65 + shift; // ascii A == 65, returns uppercase character
        }
        char dec(char y, int k){
            y = y - 65;
            int shift = (y - k) % 26;
            if (shift < 0) shift += 26;
            return 97 + shift;
        }
        
        std::string encString(){
            ys = "";
            for (char x: xs) ys += enc(x, k);
            return ys;
        }

        std::string decString(){
            xs = "";
            for (char y: ys) xs += dec(y, k);
            return xs;
        }

    public:

        Shift(){}

        Shift(std::string xs): xs(xs) {}

        Shift(std::string xs, int k): xs(xs), k(k) { encString(); }

        void set_xs(std::string xs){
            this->xs = xs;
            encString();
        }
        void set_ys(std::string ys){
            this->ys = ys;
            decString();
        }
        void set_k(int k){
            this->k = k;
            encString();
        }

        std::string get_xs() { return xs; }
        std::string get_ys() { return ys; }

};

class Affine{
    private:
        int a = 1;
        int b = 0;
        std::string xs = "";
        std::string ys = "";

        int gcd(int a, int b){
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

        int mod_inverse(int a, int m){
            a = a % m;
            for (int x = 1; x < m; x++){
                if ((a * x) % m == 1) return x;
            }
            return -1;
        }

        char enc(char x, int a, int b){
            if (x < 'a' || x > 'z') return x;
            if (gcd(a,26) != 1) return x; // should check a outside of function so it doesnt run for each char
            
            x = x - 'a';
            int affine = (a * x + b) % 26;
            return 'A' + affine;
        }

        char dec(char y, int a, int b){
            if (y < 'A' || y > 'Z') return y;
            int a_inv = mod_inverse(a, 26);
            if (a_inv == -1) return y;

            y = y - 'A';
            int affine = (a_inv * (y - b)) % 26;
            if (affine < 0) affine += 26;
            return 'a' + affine;
        }
        
        std::string encString(){
            ys = "";
            for (char x: xs) ys += enc(x, a, b);
            return ys;
        }

        std::string decString(){
            xs = "";
            for (char y: ys) xs += dec(y, a, b);
            return xs;
        }

    public:

        Affine(){}

        Affine(std::string xs){
            this->xs = xs; 
            encString();
        }

        Affine(std::string xs, int a, int b){
            this->xs = xs;
            if (gcd(a, 26) != 1) a = 1;
            this->a = a;
            this->b = b;
            encString();
        }

        void set_xs(std::string xs){
            this->xs = xs;
            encString();
        }
        void set_ys(std::string ys){
            this->ys = ys;
            decString();
        }
        void set_k(int a, int b){
            this->a = a;
            this->b = b;
            encString();
        }

        std::string get_xs() { return xs; }
        std::string get_ys() { return ys; }

};

#endif