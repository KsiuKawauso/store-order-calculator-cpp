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
    ifstream failas(FilPavad);

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
        return suma * 0.10;
    }

    return 0;
}

double skaicMokSum(double suma, double nuol) {
    return suma - nuol;
}

double skaicKatSum(
    string pasirinktaKat,
    string kat[],
    double kain[],
    int kiek[],
    int PrekKiek
) {
    double KatSum = 0;

    for (int i = 0; i < PrekKiek; i++) {
        if (kat[i] == pasirinktaKat) {
            double eilSuma = skaicEilSum(kain[i], kiek[i]);
            double nuol = skaicNuol(eilSuma, kiek[i]);

            KatSum += skaicMokSum(eilSuma, nuol);
        }
    }

    return KatSum;
}

void RodPrek(
    string kat[],
    string pavad[],
    double kain[],
    int kiek[],
    int PrekKiek,
    string PasKat = ""
) {
    bool rasta = false;

    cout << fixed << setprecision(2);

    cout << "\n";
    cout << left << setw(15) << "Kategorija"
         << setw(30) << "Preke"
         << right << setw(10) << "Kaina"
         << setw(8) << "Kiekis"
         << setw(12) << "Suma"
         << setw(12) << "Nuolaida"
         << setw(12) << "Moketina" << endl;

    cout << string(99, '-') << endl;

    for (int i = 0; i < PrekKiek; i++) {
        if (PasKat == "" || kat[i] == PasKat) {
            rasta = true;

            double suma = skaicEilSum(kain[i], kiek[i]);
            double nuol = skaicNuol(suma, kiek[i]);
            double mok = skaicMokSum(suma, nuol);

            cout << left << setw(15) << kat[i]
                 << setw(30) << pavad[i]
                 << right << setw(10) << kain[i]
                 << setw(8) << kiek[i]
                 << setw(12) << suma
                 << setw(12) << nuol
                 << setw(12) << mok << endl;
        }
    }

    if (!rasta) {
        cout << "Pasirinktoje kategorijoje prekiu nera.\n";
    }
}

void RodUzsakSum(
    double kain[],
    int kiek[],
    int PrekKiek
) {
    double SumPreNuol = 0;
    double BendNuol = 0;

    for (int i = 0; i < PrekKiek; i++) {
        double suma = skaicEilSum(kain[i], kiek[i]);
        double nuol = skaicNuol(suma, kiek[i]);

        SumPreNuol += suma;
        BendNuol += nuol;
    }

    cout << fixed << setprecision(2);
    cout << "\nSuma pries nuolaidas: "
         << SumPreNuol << " EUR\n";

    cout << "Bendra nuolaidu suma: "
         << BendNuol << " EUR\n";

    cout << "Galutine uzsakymo suma: "
         << SumPreNuol - BendNuol << " EUR\n";
}

void RodAtask(
    ostream &isvedimas,
    string kat[],
    string pavad[],
    double kain[],
    int kiek[],
    int PrekKiek
) {
    double SumPreNuol = 0;
    double BendNuol = 0;

    isvedimas << fixed << setprecision(2);

    isvedimas << "\n***** UZSAKYMO ATASKAITA *****\n";

    isvedimas << left << setw(15) << "Kategorija"
              << setw(30) << "Preke"
              << right << setw(10) << "Kaina"
              << setw(8) << "Kiekis"
              << setw(12) << "Suma"
              << setw(12) << "Nuolaida"
              << setw(12) << "Moketina" << endl;

    isvedimas << string(99, '-') << endl;

    for (int i = 0; i < PrekKiek; i++) {
        double suma = skaicEilSum(kain[i], kiek[i]);
        double nuol = skaicNuol(suma, kiek[i]);
        double mok = skaicMokSum(suma, nuol);

        SumPreNuol += suma;
        BendNuol += nuol;

        isvedimas << left << setw(15) << kat[i]
                  << setw(30) << pavad[i]
                  << right << setw(10) << kain[i]
                  << setw(8) << kiek[i]
                  << setw(12) << suma
                  << setw(12) << nuol
                  << setw(12) << mok << endl;
    }

    isvedimas << "\nSuma pries nuolaidas: "
              << SumPreNuol << " EUR\n";

    isvedimas << "Bendra nuolaidu suma: "
              << BendNuol << " EUR\n";

    isvedimas << "Galutine uzsakymo suma: "
              << SumPreNuol - BendNuol << " EUR\n";

    isvedimas << "\n========== KATEGORIJU SUVESTINE ==========\n";

    string KatPavadinimai[] = {
        "Dviraciai", "Dalys", "Aksesuarai"
    };

    for (int i = 0; i < 3; i++) {
        double KatSum = skaicKatSum(
            KatPavadinimai[i],
            kat,
            kain,
            kiek,
            PrekKiek
        );

        isvedimas << KatPavadinimai[i]
                  << ": " << KatSum << " EUR\n";
    }

    isvedimas << "========================================\n";
}

bool IssAtask(
    string failPavad,
    string kat[],
    string pavad[],
    double kain[],
    int kiek[],
    int PrekKiek
) {
    ofstream failas(failPavad);

    if (!failas.is_open()) {
        cout << "Klaida! Nepavyko sukurti ataskaitos failo.\n";
        return false;
    }

    RodAtask(
        fail,
        kat,
        pavad,
        kain,
        PrekKiek,
    );

    if (!failas) {
        cout << "Klaida! Nepavyko irasyti ataskaitos.\n";
        return false;
    }

    failas.close();

    if (!failas) {
        cout << "Klaida uzdarant ataskaitos faila.\n";
        return false;
    }

    return true;
}

int main() {
    string kat[MaxPrek];
    string pavad[MaxPrek];
    double kain[MaxPrek];
    int kiek[MaxPrek];

    int PrekKiek = 0;

    if (!nuskaitytiDuomenis(
        "uzsakymas.txt",
        kat,
        pavad,
        kain,
        kiek,
        PrekKiek
    )) {
        return 1;
    }

    cout << "Duomenys sekmingai nuskaityti.\n";

    int pasirinkimas;

    do {
        cout << "\n=*+=*+=*+= MENIU =*+=*+=*+=\n";
        cout << "1. Perziureti visas uzsakymo prekes\n";
        cout << "2. Perziureti pasirinktos kategorijos prekes\n";
        cout << "3. Perziureti viso uzsakymo sumas\n";
        cout << "4. Perziureti sumas pagal kategorijas\n";
        cout << "5. Parodyti visa uzsakymo ataskaita\n";
        cout << "6. Issaugoti ataskaita i faila\n";
        cout << "7. Iseiti\n";
        cout << "Pasirinkite veiksma: ";
        cin >> pasirinkimas;

        if (pasirinkimas < 1 || pasirinkimas > 7) {
            cout << "Klaida! Pasirinkite skaiciu nuo 1 iki 7.\n";
            continue;
        }

        if (pasirinkimas == 1) {
            RodPrek(kat, pavad, kain, kiek, PrekKiek);
        }

        else if (pasirinkimas == 2) {
            int KatPas;

            cout << "\nPasirinkite kategorija:\n";
            cout << "1. Dviraciai\n";
            cout << "2. Dalys\n";
            cout << "3. Aksesuarai\n";
            cout << "Jusu pasirinkimas: ";
            
            string pasirinktaKat;

            switch (KatPas) {
                case 1:
                    pasirinktaKat = "Dviraciai";
                    break;
                case 2:
                    pasirinktaKat = "Dalys";
                    break;
                case 3:
                    pasirinktaKat = "Aksesuarai";
                    break;
                default:
                    cout << "Klaida! Pasirinkite 1, 2 arba 3.\n";
                    continue;
            }

            RodPrek(
                kat, pavad, kain,
                kiek, PrekKiek, pasirinktaKat
            );

            double suma = skaicKatSum(
                pasirinktaKat,
                kat,
                kain,
                kiek,
                PrekKiek
            );

            cout << "Kategorijos moketina suma: "
                 << fixed << setprecision(2)
                 << suma << " EUR\n";
        }

        else if (pasirinkimas == 3) {
            RodUzsakSum(kain, kiek, PrekKiek);
        }

        else if (pasirinkimas == 4) {
            string katPavad[] = {
                "Dviraciai", "Dalys", "Aksesuarai"
            };

            for (int i = 0; i < 3; i++) {
                double suma = skaicKatSum(
                    katPavad[i],
                    kat,
                    kain,
                    kiek,
                    PrekKiek
                );

                cout << fixed << setprecision(2);
                cout << katPavad[i]
                     << ": " << suma << " EUR\n";
            }
        }

        else if (pasirinkimas == 5) {
            RodAtask(
                cout, kat, pavad,
                kain, kiek, PrekKiek
            );
        }

        else if (pasirinkimas == 6) {
            if (IssAtask(
                "ataskaita.txt",
                kat,
                pavad,
                kain,
                kiek,
                PrekKiek
            )) {
                cout << "Ataskaita sekmingai issaugota faile ataskaita.txt.\n";
            }
        }

        else if (pasirinkimas == 7) {
            cout << "Programa baigta.\n";
        }

    } while (pasirinkimas != 7);

    return 0;
}

