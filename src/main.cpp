#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

const double PI = M_PI;

double sineWave(double freq, double amp, double time);

double squareWave(double freq, double amp, double time);

double triangleWave(double freq, double amp, double time);

double sawtoothWave(double freq, double amp, double time);

double calculatePhase(double freq, double time);

vector<double> generateSamples(double freq, double amp, int rate, int numSamples, int option);

void exportCSV(const vector<double> &samples, int rate);

int main()
{

    double freq;
    double amp;
    int rate;
    double duration;

    int option;

    cout << "FUNCTION GENERATOR" << endl
         << "------------------" << endl
         << "1. Sine" << endl
         << "2. Square" << endl
         << "3. Triangle" << endl
         << "4. Sawtooth" << endl
         << endl
         << endl
         << "Select Waveform: ";

    cin >> option;

    cout << "Freq: ";
    cin >> freq;

    cout << "Amp: ";
    cin >> amp;

    cout << "Rate: ";
    cin >> rate;

    cout << "Duration: ";
    cin >> duration;

    int numSamples = rate * duration;

    vector<double> wave = generateSamples(freq, amp, rate, numSamples, option);

    exportCSV(wave, rate);

    return 0;
}

double sineWave(double freq, double amp, double time)
{
    return amp * sin(2 * PI * freq * time);
}

double squareWave(double freq, double amp, double time)
{
    double phase = calculatePhase(freq, time);

    if (phase < 0.5)
        return amp;
    else
        return -amp;
}

double triangleWave(double freq, double amp, double time)
{
    double phase = calculatePhase(freq, time);

    if (phase < 0.25)
    {
        return amp * (4 * phase);
    }
    else if (phase < 0.75)
    {
        return amp * (2 - 4 * phase);
    }
    else
    {
        return amp * (4 * phase - 4);
    }
}

double sawtoothWave(double freq, double amp, double time)
{
    double phase = calculatePhase(freq, time);

    return amp * (2 * phase - 1);
}

double calculatePhase(double freq, double time)
{
    double period = 1.0 / freq;
    return fmod(time, period) / period;
}

vector<double> generateSamples(double freq, double amp, int rate, int numSamples, int option)
{

    vector<double> wave;
    wave.reserve(numSamples);

    switch (option)
    {
    case 1:
        for (int n = 0; n < numSamples; n++)
        {
            double time = static_cast<double>(n) / rate;
            wave.push_back(sineWave(freq, amp, time));
        }
        break;
    case 2:
        for (int n = 0; n < numSamples; n++)
        {
            double time = static_cast<double>(n) / rate;
            wave.push_back(squareWave(freq, amp, time));
        }
        break;
    case 3:
        for (int n = 0; n < numSamples; n++)
        {
            double time = static_cast<double>(n) / rate;
            wave.push_back(triangleWave(freq, amp, time));
        }
        break;
    case 4:
        for (int n = 0; n < numSamples; n++)
        {
            double time = static_cast<double>(n) / rate;
            wave.push_back(sawtoothWave(freq, amp, time));
        }
        break;

    default:
        break;
    }

    return wave;
}

void exportCSV(const vector<double> &samples, int rate)
{
    ofstream file("waveform.csv");

    file << "Time,Amplitude\n";

    for (size_t n = 0; n < samples.size(); n++)
    {
        double time = static_cast<double>(n) / rate;

        file << time << "," << samples[n] << "\n";
    }

    file.close();
}