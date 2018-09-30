#include "expansion.h"

expansion::expansion()
{
    fstream in;
        in.open(FILE_INPUT_PATCH, fstream::in);
        if (!in)
            cout << "File not found";
            //return 1;

        //Ввод данных
        //Ввод диапазона
        double Range_begin, Range_end;
        in >> Range_begin >> Range_end;

        if ( Range_end - Range_begin < 0) {
            cout << "Negatve range len";
            //return 1;
        }



        while (in) {
            double x_coord, y_coord;
            in >> x_coord >> y_coord;
            if (!in) break;

            /*
            if (find(x.begin(),x.end(),x_coord) != x.end() ) {  // If x isn't unique
                cout << "Function isn't single-valued";
              //  return 1;
            }
            */ //TODO Защита от дурака

            x.push_back(x_coord);
            y.push_back(y_coord);

        }

        fstream out;
        out.open(FILE_OUTPUT_PATCH, fstream::out);
        for (double i = Range_begin; i <= Range_end; i += DELTA) {
            ostringstream strs;
            strs << i << ' ' << T(i);
            string str = strs.str();
            size_t cur;
            while ((cur = str.find(".")) != string::npos)
                str.replace(cur, 1, ",");
            out << str << '\n';
        }


        cout << "Success"<<'\n';
 }





 double expansion::T(double x_arg) {
        double value(0); // Значение функции
        int n = x.size();
        for (int m = 0; m < n; m++) {
            double numerator(1), denominator(1); // Числитель, Знаменатель
            for (int k = 0; k < n; k++)
                if (k != m) {
                    numerator *= sin((double)(x_arg - x[k]) / 2);
                    denominator *= sin((double)(x[m] - x[k]) / 2);
                }

            value += y[m] * (double)(numerator / denominator);
        }
        return value;
}
