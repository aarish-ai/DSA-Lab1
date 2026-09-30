#include <iostream>
#include <string>

using namespace std;

// Node for doubly linked list
struct SongNode {
    int songID;
    string songName;
    string duration;

    SongNode* next;
    SongNode* prev;
};

class Playlist {
private:
    SongNode* head;
    SongNode* tail;
    SongNode* currentTrack;

public:
    Playlist() {
        head = NULL;
        tail = NULL;
        currentTrack = NULL;
    }

    // 1. Add Song at end
    void addSong(int id, string name, string duration) {
        SongNode* newNode = new SongNode();
        newNode->songID = id;
        newNode->songName = name;
        newNode->duration = duration;
        newNode->next = NULL;
        newNode->prev = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
            currentTrack = head;
            cout << "Song added: " << name << endl;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;

        cout << "Song added: " << name << endl;
    }

    // 2. Delete Song by ID
    void deleteSong(int id) {
        if (head == NULL) {
            cout << "Playlist is empty!" << endl;
            return;
        }

        SongNode* temp = head;

        // search for song
        while (temp != NULL && temp->songID != id) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Song with ID " << id << " not found." << endl;
            return;
        }

        if (temp == currentTrack) {
            if (temp->next != NULL) {
                currentTrack = temp->next;
            } else {
                currentTrack = temp->prev;
            }
        }

        if (temp == head && temp == tail) {
            head = NULL;
            tail = NULL;
        } else if (temp == head) {
            head = head->next;
            head->prev = NULL;
        } else if (temp == tail) {
            tail = tail->prev;
            tail->next = NULL;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        cout << "Deleted song: " << temp->songName << " (ID: " << id << ")" << endl;
        delete temp;
    }

    // 3. Display Forward
    void displayForward() {
        if (head == NULL) {
            cout << "Playlist is empty." << endl;
            return;
        }

        cout << "\nPlaylist (Forward):" << endl;
        SongNode* temp = head;

        while (temp != NULL) {

            cout << "ID: " << temp->songID 
                 << " | Title: " << temp->songName 
                 << " | Duration: " << temp->duration << endl;

            temp = temp->next;
        }
        cout << endl;
    }

    // 4. Display Backward
    void displayBackward() {
        if (tail == NULL) {
            cout << "Playlist is empty." << endl;
            return;
        }

        cout << "\nPlaylist (Backward):" << endl;
        SongNode* temp = tail;

        while (temp != NULL) {

            cout << "ID: " << temp->songID 
                 << " | Title: " << temp->songName 
                 << " | Duration: " << temp->duration << endl;

            temp = temp->prev;
        }
        cout << endl;
    }

    // 5. Search Song
    void searchSong(int id) {
        SongNode* temp = head;

        while (temp != NULL) {
            if (temp->songID == id) {
                cout << "Song Found -> ID: " << temp->songID 
                     << ", Title: " << temp->songName 
                     << ", Duration: " << temp->duration << endl;
                return;
            }

            temp = temp->next;
        }

        cout << "Song with ID " << id << " not found in playlist." << endl;
    }

    // 6. Play Next / Previous
    void playCurrent() {
        if (currentTrack != NULL) {
            cout << "Currently Playing: " << currentTrack->songName 
                 << " (" << currentTrack->duration << ")" << endl;
        } else {
            cout << "No song currently selected." << endl;
        }
    }

    void playNext() {
        if (currentTrack == NULL) {
            cout << "Playlist is empty." << endl;
            return;
        }

        if (currentTrack->next != NULL) {
            currentTrack = currentTrack->next;
            cout << "Skipped to Next -> ";
            playCurrent();
        } else {
            cout << "Reached the end of the playlist. Cannot play next." << endl;
        }
    }

    void playPrevious() {
        if (currentTrack == NULL) {
            cout << "Playlist is empty." << endl;
            return;
        }

        if (currentTrack->prev != NULL) {
            currentTrack = currentTrack->prev;
            cout << "Moved to Previous -> ";
            playCurrent();
        } else {
            cout << "At the beginning of the playlist. Cannot play previous." << endl;
        }
    }

    // 7. Reverse Playlist in place
    void reversePlaylist() {
        if (head == NULL || head->next == NULL) {
            return;
        }

        SongNode* current = head;
        SongNode* temp = NULL;

        // swap next and prev pointers
        while (current != NULL) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;

            current = current->prev; // moves forward because prev and next swapped
        }

        if (temp != NULL) {
            tail = head;
            head = temp->prev;
        }

        cout << "Playlist reversed successfully." << endl;
    }
};

int main() {
    Playlist myPlaylist;

    cout << "Playlist Management System (Doubly Linked List)" << endl;

    // 1. Adding songs
    cout << "\n[1] Adding Songs to Playlist:" << endl;
    myPlaylist.addSong(101, "Bohemian Rhapsody", "5:55");
    myPlaylist.addSong(102, "Hotel California", "6:30");
    myPlaylist.addSong(103, "Stairway to Heaven", "8:02");
    myPlaylist.addSong(104, "Comfortably Numb", "6:21");
    myPlaylist.addSong(105, "Starboy", "3:50");

    // 2. Display Forward
    cout << "\n[2] Displaying Playlist Forward:" << endl;
    myPlaylist.displayForward();

    // 3. Display Backward
    cout << "[3] Displaying Playlist Backward:" << endl;
    myPlaylist.displayBackward();

    // 4. Searching for Songs
    cout << "[4] Searching for Songs:" << endl;
    myPlaylist.searchSong(103);
    myPlaylist.searchSong(999);

    // 5. Playing and Navigating Tracks
    cout << "\n[5] Music Player Navigation:" << endl;
    myPlaylist.playCurrent();
    myPlaylist.playNext();
    myPlaylist.playNext();
    myPlaylist.playPrevious();

    // 6. Deleting a Song
    cout << "\n[6] Deleting Song (ID 102):" << endl;
    myPlaylist.deleteSong(102);
    myPlaylist.displayForward();

    // 7. Reversing Playlist
    cout << "[7] Reversing the Entire Playlist in place:" << endl;
    myPlaylist.reversePlaylist();
    myPlaylist.displayForward();

    return 0;
}
