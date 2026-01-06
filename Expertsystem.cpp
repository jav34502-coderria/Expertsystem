#include<iostream>
#include <vector> 
#include <string>
using namespace std;

//fact structure
struct Fact {
    string name;
    bool value;
};

vector<Fact> factBase;
// ================= USER STRUCTURES =================
struct Patient {
    string username;
    string password;
};

vector<Patient> patients;

// ADMIN 
string adminUser = "admin";
string adminPass = "123";

 // functions declaration
 void patientRegister();
bool patientLogin();
bool adminLogin();
void inputFacts();
bool getFact(string name);
void showFacts();
void runExpertSystem();
void formalInference();
void explain(string msg);

//Main
int main() {
    int choice;
    bool running = true;

    while (running) {

      cout << "\n";
    cout << "  __________________________________________________________" << endl;
    cout << " /                                                          \\" << endl;
    cout << " |    __________________________________________________    |" << endl;
    cout << " |   |                                                  |   |" << endl;
    cout << " |   |      [!]  PSYCHO LOGIC EXPERT SYSTEM  [!]        |   |" << endl;
    cout << " |   |           --------------------------             |   |" << endl;
    cout << " |   |                 [ ANALYZER ]                     |   |" << endl;
    cout << " |   |__________________________________________________|   |" << endl;
    cout << " |                                                          |" << endl;
    cout << " \\__________________________________________________________/" << endl;
    
    cout << endl;
        cout << "1. Patient Register\n";
        cout << "2. Patient Login\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            patientRegister();
            break;

        case 2:
            if (patientLogin()) {
                cout << "\n--- ENTER PATIENT DATA ---\n";
                inputFacts();
                runExpertSystem();
            }
            break;

        case 3:
            if (adminLogin()) {
                int adminChoice;
                bool adminMenu = true;

                while (adminMenu) {
                    cout << "\n--- ADMIN CONTROL PANEL ---\n";
                    cout << "1. Show Fact Base\n";
                    cout << "2. Clear Fact Base\n";
                    cout << "3. Run Expert System\n";
                    cout << "4. Logout\n";
                    cout << "Choice: ";
                    cin >> adminChoice;

                    if (adminChoice == 1) {
                        showFacts();
                    }
                    else if (adminChoice == 2) {
                        factBase.clear();
                        cout << "Fact Base Cleared Successfully\n";
                    }
                    else if (adminChoice == 3) {
                        runExpertSystem();
                    }
                    else if (adminChoice == 4) {
                        adminMenu = false;
                        cout << "Admin Logged Out\n";
                    }
                    else {
                        cout << "Invalid Admin Option\n";
                    }
                }
            }
            break;

        case 4:
            cout << "System Exiting...\n";
            running = false;
            break;

        default:
            cout << "Invalid Choice!\n";
        }
    }

    return 0;
}
//facts data
void inputFacts() {
    factBase.clear();
    bool t;

    cout << "\nEnter 1 = Yes, 0 = No\n";

    cout << "Hallucinations (H): ";
     cin >> t;
      factBase.push_back({"H", t});
    cout << "Delusions (D): ";
     cin >> t; 
    factBase.push_back({"D", t});
    cout << "Disorganized Speech (S): ";
     cin >> t; factBase.push_back({"S", t});
    cout << "Negative Symptoms (N): "; cin >> t;
     factBase.push_back({"N", t});
    cout << "Social / Work Dysfunction (W): "; 
    cin >> t; 
    factBase.push_back({"W", t});
    cout << "Duration >= 6 months (M): ";
     cin >> t;
     factBase.push_back({"M", t});

    cout << "Mood Episodes (Bipolar) (B): ";
     cin >> t; factBase.push_back({"B", t});
    cout << "Severe Depression (DEP): "; cin >> t;
     factBase.push_back({"DEP", t});
    cout << "Substance Abuse (SUB): ";
     cin >> t; 
    factBase.push_back({"SUB", t});

    cout << "Suicidal Risk (SU): ";
     cin >> t; factBase.push_back({"SU", t});
    cout << "Aggression / Catatonia (AGG): "; 
    cin >> t;
     factBase.push_back({"AGG", t});
}


 //  GET FACT
bool getFact(string name) {
    for (auto &f : factBase)
        if (f.name == name)
            return f.value;
    return false;
}
 //  SHOW FACTS
void showFacts() {
    cout << "\n--- FACT BASE ---\n";
    for (auto &f : factBase)
        cout << f.name << " = " << (f.value ? "TRUE" : "FALSE") << endl;
 

}
  // EXPERT SYSTEM
void runExpertSystem() {

    bool H = getFact("H");
    bool D = getFact("D");
    bool S = getFact("S");
    bool N = getFact("N");
    bool W = getFact("W");
    bool M = getFact("M");

    bool B = getFact("B");
    bool DEP = getFact("DEP");
    bool SUB = getFact("SUB");

    bool SU = getFact("SU");
    bool AGG = getFact("AGG");

    cout << "\n  DIAGNOSTIC REASONING  \n";
    formalInference();

//PHASE DETECTION 
     
    string phase;
    if (H || D || S)
        phase = "ACTIVE(starting)";
    else if (N || W)
        phase = "PRODROMAL(moderate)";
    else
        phase = "RESIDUAL(severe)";

    cout << "Detected Phase: " << phase << endl;

    //   SEVERITY SCORING
    int score = 0;
    if (H) score += 3;
    if (D) score += 3;
    if (S) score += 2;
    if (N) score += 2;
    if (W) score += 1;

    cout << "Severity Score = " << score << endl;

     //  MUTUAL EXCLUSIVITY CHECK
    int conflictCount = (B ? 1 : 0) + (DEP ? 1 : 0) + (SUB ? 1 : 0);
    if (conflictCount > 1) {
        cout << " LOGICAL CONFLICT: Multiple primary disorders detected\n";
        cout << "Please reassess patient data\n";
        return;
    }
     //  CORE DSM LOGIC
    int symptomCount = H + D + S + N;

    bool schizophreniaCriteria =
        symptomCount >= 2 &&
        (H || D || S) &&
        M &&
        W &&
        phase == "ACTIVE" &&
        score >= 6;

      // SUBSTANCE OVERRIDE RULE
    if (SUB) {
        explain("Psychotic symptoms explained by substance use");
        cout << "\nFINAL DIAGNOSIS: SUBSTANCE-INDUCED PSYCHOSIS\n";
        cout << "Treatment: Detoxification + Monitoring\n";
        return;
    }
     //  DIFFERENTIAL DIAGNOSIS
    if (schizophreniaCriteria && !B && !DEP) {
        explain("Meets DSM criteria for schizophrenia");
        cout << "\n FINAL DIAGNOSIS: SCHIZOPHRENIA (" << phase << " PHASE)\n";

        if (SU || AGG) {
            cout << "HIGH RISK DETECTED\n";
            cout << "Immediate psychiatric intervention required\n";
        }

        cout << "\n TREATMENT PLAN \n";
        cout << "- Antipsychotic medication\n";
        cout << "- Psychosocial rehabilitation\n";
        cout << "- Long-term follow-up\n";
        return;
    }

    if (B) {
        explain("Psychosis linked with mood episodes");
        cout << "\nFINAL DIAGNOSIS: BIPOLAR DISORDER WITH PSYCHOTIC FEATURES\n";
        cout << "Treatment: Mood stabilizers + antipsychotics\n";
    }
    else if (DEP) {
        explain("Psychosis occurs exclusively during depression");
        cout << "\nFINAL DIAGNOSIS: MAJOR DEPRESSIVE DISORDER WITH PSYCHOSIS\n";
        cout << "Treatment: Antidepressants + psychotherapy\n";
    }
    else if (!M) {
        explain("Duration criteria not met");
        cout << "\nPROVISIONAL / BRIEF PSYCHOTIC DISORDER\n";
    }
    else {
        explain("Insufficient diagnostic criteria");
        cout << "\nNO CONFIRMED PSYCHOTIC DISORDER\n";
    }
}
  // FORMAL INFERENCE ENGINE
void formalInference() {

    bool H   = getFact("H");
    bool D   = getFact("D");
    bool S   = getFact("S");
    bool N   = getFact("N");
    bool W   = getFact("W");
    bool M   = getFact("M");

    bool B   = getFact("B");
    bool DEP = getFact("DEP");
    bool SUB = getFact("SUB");

    cout << "\n  FORMAL INFERENCE ENGINE (LOGIC ANALYZER) \n";

      // R1: DISJUNCTION INTRODUCTION
     //  H ⇒ (H ∨ D ∨ S)
    bool DISJ = (H || D || S);
    if (DISJ) {
        cout << "R1 Applied (Disjunction): H OR D OR S is TRUE\n";
    }

    /* 
       R2: MODUS PONENS
       (H ∨ D ∨ S) → PSY
    H ∨ D ∨ S
       ∴ PSY */
    if (DISJ) {
        factBase.push_back({"PSY", true});
        cout << "R2 Applied (Modus Ponens): PSY inferred\n";
    }

    bool PSY = getFact("PSY");

    /* 
       R3: CONJUNCTION
       PSY ∧ M ∧ W */

    if (PSY && M && W) {
        factBase.push_back({"CHRONIC_PSY", true});
        cout << "R3 Applied (Conjunction): Chronic Psychosis inferred\n";
    }

    /*
       R4: CARDINALITY RULE
       symptomCount ≥ 2 */
    int symptomCount = H + D + S + N;
    if (symptomCount >= 2) {
        cout << "R4 Applied (Cardinality Rule): >= 2 symptoms confirmed\n";
    }

    /*
       R5: DECISION RULE
       (PSY ∧ M ∧ W ∧ ≥2 symptoms) → SCH */

    if (PSY && M && W && symptomCount >= 2) {
        factBase.push_back({"SCH", true});
        cout << "R5 Applied (Decision Rule): SCH inferred\n";
    }

    /*
       R6: RULE OF EXCLUSION
       SUB → ¬SCH */
    if (SUB) {
        cout << "R6 Applied (Exclusion Rule): SCH rejected due to substance use\n";
    }

    /*
       R7: CASE ANALYSIS
       B ∨ DEP → Mood Disorder */
    if (B || DEP) {
        factBase.push_back({"MOOD_PSY", true});
        cout << "R7 Applied (Case Analysis): Mood-related psychosis inferred\n";
    }

    /* 
       R8: RESOLUTION
       (Psychosis ∨ Mood)
       ¬Mood
       ∴ Psychosis */

    if (PSY && !B && !DEP) {
        cout << "R8 Applied (Resolution): Primary Psychosis confirmed\n";
    }

    cout << "-----------------------------------------------\n";
}

//explanation
void explain(string msg) {
    cout << "→ " << msg << endl;
}
void patientRegister() {
    Patient p;
    cout << "Enter username: ";
    cin >> p.username;
    cout << "Enter password: ";
    cin >> p.password;
    patients.push_back(p);
    cout << "Patient registered successfully!\n";
}

bool patientLogin() {
    string u, p;
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;

    for (auto &pt : patients) {
        if (pt.username == u && pt.password == p) {
            cout << "Login successful!\n";
            return true;
        }
    }
    cout << "Invalid login!\n";
    return false;
}

bool adminLogin() {
    string u, p;
    cout << "Admin Username: ";
    cin >> u;
    cout << "Admin Password: ";
    cin >> p;

    if (u == adminUser && p == adminPass) {
        cout << "Admin access granted\n";
        return true;
    }
    cout << "Wrong admin credentials!\n";
    return false;
}
