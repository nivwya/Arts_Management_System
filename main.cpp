#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class Artwork {
protected:
    int id;
    string title;
    string artistName;
    string genre;
    double price;

public:
    Artwork(int id = 0, string title = "", string artistName = "", string genre = "", double price = 0.0)
        : id(id), title(title), artistName(artistName), genre(genre), price(price) {}

    virtual void display() {
        cout << setw(10) << id << setw(20) << title << setw(20) << artistName
             << setw(20) << genre << setw(10) << price << endl;
    }

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getArtistName() const { return artistName; }
    string getGenre() const { return genre; }
    double getPrice() const { return price; }

    void setPrice(double newPrice) { price = newPrice; }
};

class Painting : public Artwork {
    string medium;

public:
    Painting(int id, string title, string artistName, string genre, double price, string medium)
        : Artwork(id, title, artistName, genre, price), medium(medium) {}

    void display() override {
        Artwork::display();
        cout << setw(20) << medium << endl;
    }

    string getMedium() const { return medium; }
};

class Sculpture : public Artwork {
    double weight;

public:
    Sculpture(int id, string title, string artistName, string genre, double price, double weight)
        : Artwork(id, title, artistName, genre, price), weight(weight) {}

    void display() override {
        Artwork::display();
        cout << setw(20) << weight << " kg" << endl;
    }
    
    double getWeight() const { return weight; }
};

class ArtManagementSystem {
    vector<Artwork*> artworks;
    int nextId = 1;

public:
    ~ArtManagementSystem() {
        for (auto artwork : artworks)
            delete artwork;
    }

    void addPainting() {
        string title, artistName, genre, medium;
        double price;

        cout << "Enter title: "; cin.ignore(); getline(cin, title);
        cout << "Enter artist name: "; getline(cin, artistName);
        cout << "Enter genre: "; getline(cin, genre);
        cout << "Enter price: "; cin >> price;
        cout << "Enter medium: "; cin.ignore(); getline(cin, medium);

        artworks.push_back(new Painting(nextId++, title, artistName, genre, price, medium));
        cout << "Painting added successfully!\n";
    }

    void addSculpture() {
        string title, artistName, genre;
        double price, weight;

        cout << "Enter title: "; cin.ignore(); getline(cin, title);
        cout << "Enter artist name: "; getline(cin, artistName);
        cout << "Enter genre: "; getline(cin, genre);
        cout << "Enter price: "; cin >> price;
        cout << "Enter weight (kg): "; cin >> weight;

        artworks.push_back(new Sculpture(nextId++, title, artistName, genre, price, weight));
        cout << "Sculpture added successfully!\n";
    }

    void displayArtworks() {
        cout << left << setw(10) << "ID" << setw(20) << "Title" << setw(20) << "Artist"
             << setw(20) << "Genre" << setw(10) << "Price" << setw(20) << "Extra Info" << endl;
        cout << string(100, '-') << endl;

        for (const auto& artwork : artworks)
            artwork->display();
    }

    void updatePrice() {
        int id;
        double newPrice;
        cout << "Enter Artwork ID to update price: ";
        cin >> id;

        bool found = false;
        for (auto& artwork : artworks) {
            if (artwork->getId() == id) {
                cout << "Current price: " << artwork->getPrice() << endl;
                cout << "Enter new price: ";
                cin >> newPrice;
                artwork->setPrice(newPrice);
                found = true;
                cout << "Price updated successfully!\n";
                break;
            }
        }
        if (!found) cout << "Artwork ID not found.\n";
    }

    void removeArtwork() {
        int id;
        cout << "Enter Artwork ID to delete: ";
        cin >> id;

        auto it = find_if(artworks.begin(), artworks.end(), [id](Artwork* artwork) {
            return artwork->getId() == id;
        });

        if (it != artworks.end()) {
            delete *it;
            artworks.erase(it);
            cout << "Artwork deleted successfully!\n";
        } else {
            cout << "Artwork ID not found.\n";
        }
    }

    void saveToFile() {
        ofstream outFile("artworks.txt");

        for (const auto& artwork : artworks) {
            outFile << artwork->getId() << "|" << artwork->getTitle() << "|" << artwork->getArtistName()
                    << "|" << artwork->getGenre() << "|" << artwork->getPrice();

            if (Painting* painting = dynamic_cast<Painting*>(artwork)) {
                outFile << "|Painting|" << painting->getMedium() << "\n";
            } else if (Sculpture* sculpture = dynamic_cast<Sculpture*>(artwork)) {
                outFile << "|Sculpture|" << sculpture->getWeight() << "\n";
            }
        }
        outFile.close();
        cout << "Data saved to file successfully!\n";
    }

    void loadFromFile() {
        ifstream inFile("artworks.txt");

        if (!inFile) {
            cout << "No data file found.\n";
            return;
        }

        string line, title, artistName, genre, extraInfo, type;
        int id;
        double price;

        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, title, '|');
            ss >> id;
            getline(ss, title, '|');
            getline(ss, artistName, '|');
            getline(ss, genre, '|');
            ss >> price;
            getline(ss, type, '|');
            getline(ss, extraInfo);

            if (type == "Painting") {
                artworks.push_back(new Painting(id, title, artistName, genre, price, extraInfo));
            } else if (type == "Sculpture") {
                artworks.push_back(new Sculpture(id, title, artistName, genre, price, stod(extraInfo)));
            }
        }
        inFile.close();
        cout << "Data loaded from file successfully!\n";
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n--- Art Management System ---\n";
            cout << "1. Add Painting\n";
            cout << "2. Add Sculpture\n";
            cout << "3. Display All Artworks\n";
            cout << "4. Update Artwork Price\n";
            cout << "5. Remove Artwork\n";
            cout << "6. Save to File\n";
            cout << "7. Load from File\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addPainting(); break;
                case 2: addSculpture(); break;
                case 3: displayArtworks(); break;
                case 4: updatePrice(); break;
                case 5: removeArtwork(); break;
                case 6: saveToFile(); break;
                case 7: loadFromFile(); break;
                case 0: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    ArtManagementSystem system;
    system.showMenu();
    return 0;
}
