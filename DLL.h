#pragma once
#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Song
{
public:
    string name;
    string artist;
    int    duration;
    static int count;
    int id;

    Song() : name(""), artist(""), duration(0), id(0) {}
    Song(const string& n, const string& a, int d)
        : name(n), artist(a), duration(d) {

        ifstream fin("Songs.txt");
        fin >> count;
        fin.ignore(); // ignore newline after count;
        id = count + 1; // Assign a new ID based on the count
        fin.close();
    }
    void writeSong() const
    {
        string n = name;
        string a = artist;
        int d = duration;
        // Open file in append mode

        ofstream file("Songs.txt", ios::app);
        if (file.is_open()) {
            file << n << endl;
            file << a << endl;
            file << d << endl;
            count++;
            file.close();
        }
        else {
            cerr << "Error opening file for writing." << endl;
        }
    }
    Song readSong(ifstream& file, int iid)
    {
        int id;
        string n, a;
        int d;
        while (!file.eof()) {
            file >> id;
            if (id == iid) break; // Find the song with the matching ID
            file >> id;
            getline(file, n, ',');
            getline(file, a, ',');
            file >> d;
            file.ignore();
        }
        file >> id;
        getline(file, n, ',');
        getline(file, a, ',');
        file >> d;
        file.ignore(); // ignore newline after duration
        return Song(n, a, d);
    }
    void readFile()
    {
        ifstream file("Songs.txt");
        int id;
        string line;
        file >> id;
        while (!file.eof()) {
            Song song;
            while (!file.eof()) {
                file >> song.id;
                getline(file, song.name, ',');
                getline(file, song.artist, ',');
                file >> song.duration;
                cout<< "ID: " << song.id << ", Name: " << song.name 
					<< ", Artist: " << song.artist << ", Duration: " << song.duration << endl;
            }
        } // Read the count
    }
    Song getSongByID(int iid) const
    {
        ifstream file("Songs.txt");
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return Song();
        }
        int id, dur;
        file >> id;
        Song song;
        while(!file.eof()) {
            file >> song.id;
            getline(file, song.name, ',');
            getline(file, song.artist, ',');
            file >> song.duration;
            if(song.id == iid) {
                return song; // Return the song with the matching ID
			}
		}
        return Song();
	}
};

class Node
{
public:
    Song  s;
    Node* next;
    Node* prev;

    Node(const Song& song)
        : s(song), next(nullptr), prev(nullptr) {
    }
};

class CDLL
{
    Node* head;

public:
    CDLL() : head(nullptr) {}
    ~CDLL() { clear(); }

    void clear();

    bool isEmpty() const { return head == nullptr; }

    void insertFront(const Song& song);
    void insertBack(const Song& song);
    bool deleteFront();
    bool deleteBack();
    bool deleteByName(const string& name);
    bool deleteByID(const int id);

    Node* search(const int id) const;
    Node* search(const string& n) const;
    Song lastSong() const;
    void displayForward() const;
    void displayBackward() const;
    void displayCurr(const Song s) const;
    Song nextS(const Song s) const;
    Song prevS(const Song s) const;
    Song crrRet();
};
ifstream& operator>>(ifstream& is, Song& data);
ofstream& operator<<(ofstream& is, Song& data);