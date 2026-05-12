#include <windows.h>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

class Client {
private:
    std::string nom;
    std::string prenom;
    double dernierKilometrage;
    double dernierPlein;
    double tauxConsommation;
public:
    Client(std::string n, std::string p, double km, double essence)
        : nom(n), prenom(p), dernierKilometrage(km), dernierPlein(essence), tauxConsommation(0.0) {}

    bool ajouterPassage(double nouveauKm, double nouvelleEssence) {
        double distance = nouveauKm - dernierKilometrage;
        if (distance <= 0) return false; 
        tauxConsommation = (dernierPlein / distance) * 100.0;
        dernierKilometrage = nouveauKm;
        dernierPlein = nouvelleEssence;
        return true;
    }
    std::string getNomComplet() const { return prenom + " " + nom; }
    double getDernierKm() const { return dernierKilometrage; }
    double getTauxConsommation() const { return tauxConsommation; }
};


Client* clientActif = NULL;
HWND hNom, hPrenom, hKmInitial, hEssenceInitiale, hNouveauKm, hNouvelleEssence;
HWND hBtnEnregistrer, hBtnCalculer;
HWND hLabelResultat;


void MettreAJourAffichage() {
    if (!clientActif) return;

    std::stringstream ss;
    ss << "Client: " << clientActif->getNomComplet().c_str() << "\r\n"
       << "Dernier KM: " << clientActif->getDernierKm() << " km\r\n"
       << "Consommation: ";
    
    double conso = clientActif->getTauxConsommation();
    if (conso > 0) {
        ss << std::fixed << std::setprecision(2) << conso << " L/100km";
    } else {
        ss << "Non calculee";
    }
    
    SetWindowTextA(hLabelResultat, ss.str().c_str());
}

void OnEnregistrerClicked() {
    char buffer[256];
    
    GetWindowTextA(hNom, buffer, 256);
    std::string nom(buffer);

    GetWindowTextA(hPrenom, buffer, 256);
    std::string prenom(buffer);

    GetWindowTextA(hKmInitial, buffer, 256);
    double km = atof(buffer);

    GetWindowTextA(hEssenceInitiale, buffer, 256);
    double essence = atof(buffer);

    if (nom.empty() || prenom.empty()) {
        MessageBoxA(NULL, "Le nom et le prenom sont obligatoires.", "Erreur", MB_OK | MB_ICONERROR);
        return;
    }

    delete clientActif;
    clientActif = new Client(nom, prenom, km, essence);

    MessageBoxA(NULL, "Client enregistre avec succes !", "Succes", MB_OK);
    
    EnableWindow(hNouveauKm, TRUE);
    EnableWindow(hNouvelleEssence, TRUE);
    EnableWindow(hBtnCalculer, TRUE);

    MettreAJourAffichage();
}

void OnCalculerClicked() {
    if (!clientActif) {
        MessageBoxA(NULL, "Veuillez d'abord enregistrer un client.", "Erreur", MB_OK | MB_ICONERROR);
        return;
    }

    char buffer[256];

    GetWindowTextA(hNouveauKm, buffer, 256);
    double nouveauKm = atof(buffer);

    GetWindowTextA(hNouvelleEssence, buffer, 256);
    double nouvelleEssence = atof(buffer);

    if (clientActif->ajouterPassage(nouveauKm, nouvelleEssence)) {
        MessageBoxA(NULL, "Calcul de la consommation reussi !", "Succes", MB_OK);
        MettreAJourAffichage();
    } else {
        MessageBoxA(NULL, "Donnees invalides. Le nouveau kilometrage doit etre superieur à l'ancien.", "Erreur de Calcul", MB_OK | MB_ICONERROR);
    }
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
        {
            CreateWindowA("STATIC", "Nom:", WS_VISIBLE | WS_CHILD, 10, 10, 150, 20, hwnd, NULL, NULL, NULL);
            hNom = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 170, 10, 200, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindowA("STATIC", "Prenom:", WS_VISIBLE | WS_CHILD, 10, 40, 150, 20, hwnd, NULL, NULL, NULL);
            hPrenom = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 170, 40, 200, 20, hwnd, NULL, NULL, NULL);

            CreateWindowA("STATIC", "KM Initial:", WS_VISIBLE | WS_CHILD, 10, 70, 150, 20, hwnd, NULL, NULL, NULL);
            hKmInitial = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 170, 70, 200, 20, hwnd, NULL, NULL, NULL);

            CreateWindowA("STATIC", "Essence Initiale (L):", WS_VISIBLE | WS_CHILD, 10, 100, 150, 20, hwnd, NULL, NULL, NULL);
            hEssenceInitiale = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 170, 100, 200, 20, hwnd, NULL, NULL, NULL);

            hBtnEnregistrer = CreateWindowA("BUTTON", "Enregistrer Client", WS_VISIBLE | WS_CHILD, 170, 130, 200, 30, hwnd, (HMENU)1, NULL, NULL);

            CreateWindowA("STATIC", "Nouveau KM:", WS_VISIBLE | WS_CHILD, 10, 180, 150, 20, hwnd, NULL, NULL, NULL);
            hNouveauKm = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_DISABLED, 170, 180, 200, 20, hwnd, NULL, NULL, NULL);

            CreateWindowA("STATIC", "Nouvelle Essence (L):", WS_VISIBLE | WS_CHILD, 10, 210, 150, 20, hwnd, NULL, NULL, NULL);
            hNouvelleEssence = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_DISABLED, 170, 210, 200, 20, hwnd, NULL, NULL, NULL);

            hBtnCalculer = CreateWindowA("BUTTON", "Calculer Consommation", WS_VISIBLE | WS_CHILD | WS_DISABLED, 170, 240, 200, 30, hwnd, (HMENU)2, NULL, NULL);

            hLabelResultat = CreateWindowA("STATIC", "Veuillez enregistrer un client.", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 290, 360, 100, hwnd, NULL, NULL, NULL);
        }
        break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                OnEnregistrerClicked();
            }
            if (LOWORD(wParam) == 2) {
                OnCalculerClicked();
            }
            break;

        case WM_DESTROY:
            delete clientActif;
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "Sample Window Class";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(0, CLASS_NAME, "Gestion Station Essence",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 450,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
