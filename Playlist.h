#pragma once
#include "DLL.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Playlist
{
public:
    CDLL play;

    void addToList(const Song& s) {
        play.insertFront(s);
    }

    bool delFromList(const Song& s) {
        return play.deleteByID(s.id);
    }

    void displayList() const {
        play.displayForward();
    }

    void displayListBack() const {
        play.displayBackward();
    }

    Song nextS(const Song& s) const {
        return play.nextS(s);
    }

    Song prevS(const Song& s) const {
        return play.prevS(s);
    }

    void displayCurr(const Song& s) const {
        play.displayCurr(s);
    }

    bool isEmpty() const {
        return play.isEmpty();
    }

    void clear() {
        play.clear();
    }

    void insertFront(const Song& song) {
        play.insertFront(song);
    }

    void insertBack(const Song& song) {
        play.insertBack(song);
    }

    bool deleteFront() {
        return play.deleteFront();
    }

    bool deleteBack() {
        return play.deleteBack();
    }

    bool deleteByName(const string& name) {
        return play.deleteByName(name);
    }

    Song search(const int id) const {
        Node* found = play.search(id);
        if (found) {
            return found->s;
        }
        return Song();
    }
    Song crrSong() {
        return play.crrRet();
    }
    Song lastSong() const {
		return play.lastSong();
	}
    bool exist(int id) {
        return play.search(id) != nullptr;
	}
};

class user
{
public:
    string name;
    string uid;
    string phoneN;
    string password;
    Playlist playlist;

    user() : name(), uid(), phoneN(), password() {}

    user(const string& n, const string& u, string& p, const string& pass)
        : name(n), uid(u), phoneN(p), password(pass) {
        p += ".txt";
        ofstream fout(p);
        if (fout.is_open()) {
            fout << password << endl;
            fout << name << endl;
            fout << uid << endl;
            fout << phoneN << endl;

            fout.close();
        }
        else {
            cerr << "Error opening file for writing." << endl;
        }
    }

    bool checkPassword(const string& pass) const {
        return password == pass;
    }
    void addSongToPlaylist(const Song& s) {
        playlist.addToList(s);
		ofstream file(phoneN + ".txt", ios::app);
//		file << s.id << " " << s.name << ", " << s.artist << ", " << s.duration << endl;
    }
    void removeSongFromPlaylist(const Song& s) {
        playlist.delFromList(s);
    }
    void displayPlaylist() const {
        playlist.displayList();
    }
    void displayPlaylistBack() const {
        playlist.displayListBack();
    }
    void displayCurrentSong(const Song s) const {
        cout << "Now Playing: ";
        playlist.displayCurr(s);
    }
    void clearPlaylist() {
        playlist.clear();
    }
    void insertSongFront(const Song& song) {
        playlist.insertFront(song);
    }
    void insertSongBack(const Song& song) {
        playlist.insertBack(song);
    }
    bool deleteSongFront() {
        return playlist.deleteFront();
    }
    bool deleteSongBack() {
        return playlist.deleteBack();
    }
    bool deleteSongByName(const string& name) {
        return playlist.deleteByName(name);
    }
    Song searchSong(const int id) const {
        return playlist.search(id);
    }
    Song nextSong(const Song& s) const {
        return playlist.nextS(s);
	}
    Song prevSong(const Song& s) const {
        return playlist.prevS(s);
	}
    bool isPlaylistEmpty() const {
        return playlist.isEmpty();
    }
    void addToPlaylist(const Song& s) {
        playlist.addToList(s);
		ofstream file(phoneN + ".txt", ios::app);
		file << s.id << " " << s.name << ", " << s.artist << ", " << s.duration << endl;
		file.close();
    }
    void removeFromPlaylist(const Song s) {
        playlist.delFromList(s);
    }
    bool verify(string pH, string pass)
    {
        pH += ".txt";
        ifstream file(pH);
        if (!file.is_open()) {
            cerr << "Error opening File" << endl;
            return false;
        }
        string line;
        while (getline(file, line)) {
            if (line == pass) {
                getline(file, name);
                getline(file, uid);
                getline(file, phoneN);
                password = line;
                Song s;
                while (!file.eof())
                {
                    file >> s;
                    addSongToPlaylist(s);
                }

                file.close();

                return true; // Password found
            }
        }
        file.close();
        return false; // Password not found
    }
    Song retCrr()
    {
        return playlist.crrSong();
    }
    Song lastSong() const {
		return playlist.lastSong();
	}
    bool exist(int id)
    {
		return playlist.exist(id);
    }
};
