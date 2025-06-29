#include "Playlist.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

void deleteCurrentSongFromFile(const string& filename, const Song& toDelete) {
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");
    string line, artist, name;
	int id, duration;
    bool skip = false;

    getline(inFile, line);
	tempFile << line << endl; // Copy header line
    getline(inFile, line);
    tempFile << line << endl; // Copy header line
    getline(inFile, line);
    tempFile << line << endl; // Copy header line
    getline(inFile, line);
    tempFile << line << endl << endl; // Copy header line
    inFile.ignore();

    while (!inFile.eof()) {
        // Check if this line matches the song to delete (by name, artist, and duration)
        inFile >> id;
        getline(inFile, name, ',');
        getline(inFile, artist, ',');
        inFile >> duration;
        if (id != toDelete.id) 
        {
            tempFile << id << "" << name << "," << artist << ", " << duration << endl;
        } 
    }
    inFile.close();
    tempFile.close();

    // Copy temp file back to original using rdbuf
    ifstream src("temp.txt", ios::binary);
    ofstream dst(filename, ios::binary | ios::trunc);
    dst << src.rdbuf();
    src.close();
    dst.close();
    remove("temp.txt");
}

int main() {

    string n, u, p, pass;
    int dec = 0, count = 0;
    cout << "Press [1] to Sign in or Press [2] to Sign up Press [0] to exit" << endl;
    cin >> dec;

    while (dec != 1 || dec != 2 || dec != 0)
    {

        if (dec == 1)
        {
            cout << "\t\tSign In" << endl;
            cout << "Enter Phone Number: ";
            cin >> p;
            user U;
            do {
                cout << "Enter Password: ";
                cin >> pass;
                count++;
                if(count > 3)
                {
                    cout << "Too many attempts. Exiting..." << endl;
                    return 0;
				}
            } while (!U.verify(p, pass) && count <= 3);
            Song s = U.retCrr();
            cout << "Welcome " << U.name << "!" << endl;
			int deec = 0;
             do {
                 cout << "[1] Add Song to Playlist\n[2] Delete Current Song\n[3] Play Next Song\n[4] Play Previous Song \n[5] Show Current Song \n[6] Display Playlist Forward \n[7] Display Playlist Backward \n[8] Play First Song \n[9] Play Last Song \n[0] LOG OUT\n";
                 cin >> deec;

                 if (deec == 5)
                 {
                     U.displayCurrentSong(s);
                 }
                 else if (deec == 3)
                 {
                     s = U.nextSong(s);
                     U.displayCurrentSong(s);
                 }
                 else if (deec == 4)
                 {
                     s = U.prevSong(s);
                     U.displayCurrentSong(s);
                 }
                 else if (deec == 1)
                 {
                     s.readFile();
                     int id;
					 cout << "Enter Song ID: ";
					 cin >> id;
                     if (U.exist(id))
                     {
                         cout << "Song with ID " << id << " already exists in the playlist." << endl;
                     }
                     else {
                         cout << "Adding song with ID " << id << " to playlist." << endl;
                         // Add song to playlist
                         s = s.getSongByID(id);
                         U.addToPlaylist(s);
                     }
                 }
                 else if (deec == 2)
                 {
                     Song tempm = s;
                     U.removeSongFromPlaylist(s); // Remove from playlist in memory
                     deleteCurrentSongFromFile(U.phoneN + ".txt", s); // Remove from file
                     s = U.nextSong(tempm);
                     s = U.nextSong(s);
                     s = U.nextSong(s);// Move to next song after deletion
                     cout << "Current song deleted.\n";
                 }
                 else if (deec == 6)
                 {
                     U.displayPlaylist();
                 }
                 else if(deec == 7)
                 {
                     U.displayPlaylistBack();
                 }
                 else if (deec == 8)
                 {
                     s = U.retCrr();
                     U.displayCurrentSong(s);
                 }
                 else if (deec == 9)
                 {
                     s = U.lastSong();
                     U.displayCurrentSong(s);
                 }
                 else if (deec == 0)
                 {
                     cout << "Logging out..." << endl;
                     break;
				 }
             } while (deec != 1 || deec != 2 || deec != 3 || deec != 4 || deec != 5 || deec != 6 || deec != 7);
        }
        else if (dec == 2)
        {
            cout << "\t\tSign Up" << endl;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, n, '\n');
            cin.ignore();
            cout << "Enter Uid: ";
            cin >> u;
            do {
                cout << "Enter Phone Number: ";
                cin.ignore();
                cin >> p;
                ifstream fin;
                fin.open(p + ".txt"); // Just for checking, do not modify p
                if (fin.is_open())
                    cout << "Phone Number Already Exists" << endl;
                else break;
            } while (1);
            cin.ignore();
            cout << "Enter Password: ";
            getline(cin, pass);
            user U(n, u, p, pass);
        }
        else break;

        cout << "Press [1] to Sign in or Press [2] to Sign up Press [0] to exit" << endl;
        cin >> dec;

    }


    return 0;
}

