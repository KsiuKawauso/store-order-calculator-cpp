#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

const int MaxPrek = 100;

bool SkatOrdr(
    string FPavad,
    string kat[],
    string pav[],
    double kain[],
    int kiek[],
    int &PrekKiek
) {
    ifstream failas(uzsakymas.txt);

    if (!failas.is_open()) {
        cout << "Klaida! Nepavyko atidaryti duomenu failo.\n";
        return false;
    }

    string eilute;

    if (!getline(failas, eilute)) {
        cout << "Klaida! Failas tuscias.\n";
        return false;
    }

    stringstream PirmEil(eilute);

    if (!(PirmEil >> PrekKiek) ||
        (PirmEil >> ws && !PirmEil.eof())) {
        cout << "Klaida! Neteisingas prekiu skaicius.\n";
        return false;
        }

    if (PrekKiek < 1 || PrekKiek > MaxPrek) {
        cout << "Klaida! Prekiu skaicius turi buti nuo 1 iki 100.\n";
        return false;
    }

    for (int i = 0; i < PrekKiek; i++) {
        if (!getline(failas, eilute)) {
            cout << "Klaida! Nepavyko nuskaityti visu prekiu.\n";
            return false;
        }

        stringstream ss(eilute);
        string kainaTxt;
        string kiekTxt;

        if (!getline(ss, kat[i], ';') ||
            !getline(ss, pav[i], ';') ||
            !getline(ss, kainaTxt, ';') ||
            !getline(ss, kiekTxt)) {
            cout << "Klaida! Netinkamas duomenu eilutes formatas.\n";
            return false;
            }

        if (kat[i] != "Dviraciai" &&
            kat[i] != "Dalys" &&
            kat[i] != "Aksesuarai") {
            cout << "Klaida! Nezinoma prekes kategorija.\n";
            return false;
            }

        stringstream kainaGij(kainaTxt);
        stringstream kiekGij(kiekTxt);

        char papildomas;

        if (!(kainaGij >> kain[i]) ||
            (kainaGij >> papildomas) ||
            !(kiekGij >> kiek[i]) ||
            (kiekGij >> papildomas)) {
            cout << "Klaida! Netinkama kaina arba kiekis.\n";
            return false;
            }

        if (kain[i] <= 0 || kiek[i] <= 0) {
            cout << "Klaida! Kaina ir kiekis turi buti teigiami.\n";
            return false;
        }
    }

    failas.close();
    return true;
}

double skaicEilSum(double kain, int kiek) {
    return kain * kiek;
}

double skaicNuol(double sum, int kiek) {
    if (kiek >= 10) {
        return sum * 0.10;
    }

    return 0;
}

double skaicMokSum(double sum, double nuol) {
    return sum - nuol;
}

double skaicKatSum(
    string kat,
    string kat[],
    double kain[],
    int kiek[],
    int prekKiek
) {
    double KatSum = 0;

    for (int i = 0; i < prekKiek; i++) {
        if (kat[i] == kat) {
            double eilSuma =
                skaicEilSum(kainos[i], kiek[i]);

            double nuol =
                skaicNuol(eilSum, kiek[i]);

            KatSum += skaicMokSum(eilSum, nuol);
        }
    }

    return KatSum;
}

