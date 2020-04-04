/*
 *
 * This file is a cpp file for converting a png file
 * to a bitmap with customized values.
 * one value is corresponding to a pixel which is calculated
 * from the rgaba values of that pixel.
 *
 * white is 255,255,255
 * black is 0 0 0,
 * the map background should be black, and values are reversed
 * in claculation.
 *
 * discretization(cells): 3056 1638
 * obsthresh: 254
 * cost_inscribed_thresh: 100
 * cost_possibly_circumscribed_thresh: 30
 * cellsize(meters): 0.025
 * nominalvel(mpersecs): 1.0
 * timetoturn45degsinplace(secs): 2.0
 * start(meters,rads): 0.11 0.11 0
 * end(meters,rads): 74.0 39.0 0
 * environment:
 *
 *
 *
 *Author: Wei Du.
 *Date: 22/2/2018
 *Version: 1.0   ( built without cmake)
 *
 *Description: needed to be converted into object oriented
 *
 */

#include "yspng.cpp"
#include "yspng.h"

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    YsRawPngDecoder png;
    int wid, hei;
    unsigned char *rgba;
    char *inputfilename;
    char *outputfilename;
    double data;
    ofstream outputfile;

    /* load file*/
    if (1 == argc) {
        cout << "input a png file name please.\n";
        return 0;
    }

    if (2 == argc) {
        cout << "input a output file name please.\n";
        return 0;
    }

    inputfilename = argv[1];
    outputfilename = argv[2];

    if (YSOK != png.Decode(inputfilename)) {
        cout << "Cannot Opne file.\n";
        return 0;
    }

    // considering the order of storing the data,
    // there's no need to filp the picture.

    // png.Flip();

    wid = png.wid;
    hei = png.hei;
    outputfile.open(outputfilename);

    // png.rgba is unsigned char with length wid*hei*4
    rgba = png.rgba;

    // outputfile<< "discretization(cells): 3056 1638"<<endl;
    // outputfile<< "obsthresh: 254"<<endl;
    // outputfile<< "cost_inscribed_thresh: 100"<<endl;
    // outputfile<< "cost_possibly_circumscribed_thresh: 30"<<endl;
    // outputfile<< "cellsize(meters): 0.025"<<endl;
    // outputfile<< "nominalvel(mpersecs): 1.0"<<endl;
    // outputfile<< "timetoturn45degsinplace(secs): 2.0"<<endl;
    // outputfile<< "start(meters,rads): 0.11 0.11 0"<<endl;
    // outputfile<< "end(meters,rads): 74.0 39.0 0"<<endl;
    // outputfile<< "environment:"<<endl;

    for (int i = 0; i < hei; ++i) {     // row
        for (int j = 0; j < wid; ++j) { // column

            int index = (i * wid + j) * 4;
            data = rgba[index] + rgba[index + 1] + rgba[index + 2];
            data = data/3.0;
            //data = 255 - data / 3.0;
            // if (data > 254) data = 254;
            // outputfile<< (int)data<<" ";
            if (data > 253.00) {                    // white
                outputfile << "0,";
            } else if (data > 5.00) {               // blue
                outputfile << "20,";
            } else {                                // black
                outputfile << "-1,";
            }
        }
        outputfile << endl;
    }

    outputfile.close();
    return 0;
}

