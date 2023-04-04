#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct IMDB
{
    int rank;
    string name;
    int year;
    double rating;
    string genre;
    string certificate;
    string run_time;
    long budget;
    long box_office;
    string casts;
    string directors;
    string writers;
};

vector<IMDB> docFile(string path)
{
    vector<IMDB> imdb;
    ifstream inFile;
    inFile.open(path);
    if (!inFile.is_open())
    {
        cout << "Khong the mo file";
        exit(0);
    }
    string line;
    getline(inFile, line);
    while (getline(inFile, line))
    {
        IMDB im;
        istringstream iss(line);
        string token;

        getline(iss, token, ',');
        im.rank = stoi(token);

        getline(iss, token, ',');
        im.name = token;

        getline(iss, token, ',');
        im.year = stoi(token);

        getline(iss, token, ',');
        im.rating = stod(token);

        getline(iss, token, ',');
        im.genre = token;

        getline(iss, token, ',');
        im.certificate = token;

        getline(iss, token, ',');
        im.run_time = token;

        getline(iss, token, ',');
        im.budget = stoi(token);

        getline(iss, token, ',');
        im.box_office = stoi(token);

        getline(iss, token, ',');
        im.casts = token;

        getline(iss, token, ',');
        im.directors = token;

        getline(iss, token, ',');
        im.writers = token;

        imdb.push_back(im);
    }
    inFile.close();
    return imdb;
}

void inFile(vector<IMDB> &imdb, string &directorName)
{
    long total = 0;
    for (auto &im : imdb)
    {
        if (im.directors == directorName)
        {
            cout << im.rank << ", " << im.name << ", " << im.directors << endl;
            total += im.box_office;
        }
    }
    cout << total;
}

int toHours(string run_time)
{
    int hour_pos = run_time.find("h");
    int min_pos = run_time.find("m");
    int hour = 0;
    int minute = 0;
    if (hour_pos != string::npos)
    {
        hour = stoi(run_time.substr(0, hour_pos));
    }
    if (min_pos != string::npos)
    {
        minute = stoi(run_time.substr(hour_pos + 2, min_pos - hour_pos - 2));
    }
    return hour + minute / 60;
}

int dem(vector<IMDB> &imdb, string run_time)
{
    int dem = 0;
    int target_hours = toHours(run_time);
    for (auto &im : imdb)
    {
        if (toHours(im.run_time) >= target_hours)
        {
            cout << im.rank << ", " << im.run_time << endl;
            dem++;
        }
    }
    return dem;
}

void outFile(vector<IMDB> imdb, string &actName)
{
    ofstream outFile;
    outFile.open("output.txt");
    for (auto &im : imdb)
    {
        if (im.casts.find(actName) != string::npos)
        {
            outFile << im.rank << ", " << im.name << ", " << im.casts << endl
                    << endl;
        }
    }
    outFile.close();
}

int main(int argc, char *argv[])
{
    if (argc < 9)
    {
        cout << "Invalid input";
        exit(0);
    }
    string path, directorName, actName;
    double run_time;
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == string("-i"))
        {
            path = argv[i + 1];
        }
        if (string(argv[i]) == string("-p"))
        {
            directorName = argv[i + 1];
            int j = i + 1;
            while (string(argv[j + 1]) != string("-i") && string(argv[j + 1]) != string("-w") && string(argv[j + 1]) != string("-h"))
            {
                directorName += " ";
                directorName += argv[j + 1];
                j++;
            }
        }
        if (string(argv[i]) == string("-w"))
        {
            actName = argv[i + 1];
        }
        if (string(argv[i]) == string("-h"))
        {
            run_time = stod(argv[i + 1]);
        }
    }
    vector<IMDB> imdb = docFile(path);
    inFile(imdb, directorName);
    int count = dem(imdb, to_string(run_time));
}