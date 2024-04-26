
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

namespace PolygonalLibrary{
bool ImportMesh(const string& filepath,
                PolygonalMesh& mesh){
    if(!ImportCell0Ds(filepath +"/Cell0Ds.csv",mesh))
    {
        return false;
    }

    else if(!ImportCell1Ds(filepath+ "/Cell1Ds.csv", mesh)){
        return false;
    }

    else if(!ImportCell2Ds(filepath + "/Cell2Ds.csv",
                       mesh))
    {
        return false;
    }

    return true;
}



bool ImportCell0Ds(const string &filename, PolygonalMesh& mesh){

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;
    list<string> listLines;
    string line;
    while(getline(file,line))
        listLines.push_back(line); // aggiungere elemento a fine lista
    file.close();

    listLines.pop_front(); // togliere elemento inizio lista
    mesh.NumberCell0D = listLines.size();

    if (mesh.NumberCell0D == 0)
    {
        cerr << "Non ci sono celle 0D" << endl;
        return false;
    }

    // preallocare la memoria
    mesh.idCell0D.reserve(mesh.NumberCell0D);
    mesh.CoordinatesCell0Ds.reserve(mesh.NumberCell0D);

    for (const string& line: listLines)
    {
        istringstream  converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;
        char delimiter;
        converter >> id >> delimiter>>marker>> delimiter >> coord(0)>> delimiter >> coord(1);

        mesh.idCell0D.push_back(id);
        mesh.CoordinatesCell0Ds.push_back(coord);

        if(marker != 0){
            auto ret = mesh.Cell0DMarkers.insert({marker,{id}});
            // si inserisce una nuova coppia chiave-valore
            // ret contiene iteratore posizione nuovo elemento inserito

            if(!ret.second)
                // inserimento non avvenuto con successo
                (ret.first)->second.push_back(id);
        }
    }
    file.close();
    return true;

}








bool ImportCell1Ds(const string &filename, PolygonalMesh& mesh)
{
    ifstream file;
    file.open(filename);
    if(file.fail())
        return false;
    list<string> listLines;
    string line;
    while (getline(file,line))
        listLines.push_back(line);
    file.close();

    listLines.pop_front();

    mesh.NumberCell1D = listLines.size();

    if(mesh.NumberCell1D == 0)
    {
        cerr<< "Non ci sono celle 1D" << endl;
        return false;
    }
    mesh.idCell1D.reserve(mesh.NumberCell1D);
    mesh.VerticesCell1D.reserve(mesh.NumberCell1D);

    for (const string& line: listLines){
        istringstream converter(line);
        unsigned int id;
        unsigned int marker;
        Vector2d vertices;
        char delimiter;
        converter >> id >>delimiter>> marker >>delimiter>> vertices(0) >>delimiter>> vertices(1);

        mesh.idCell1D.push_back(id);
        mesh.VerticesCell1D.push_back(vertices);

        if(marker != 0){
            auto ret = mesh.Cell1DMarkers.insert({marker,{id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }
    }

    file.close();
    return true;
}





bool ImportCell2Ds(const string &filename, PolygonalMesh& mesh)
{
    ifstream file;
    file.open(filename);
    if(file.fail())
        return false;
    list<string> listLines;
    string line;
    while (getline(file,line))
        listLines.push_back(line);
    file.close();

    listLines.pop_front();

    mesh.NumberCell2D = listLines.size();

    if(mesh.NumberCell2D == 0)
    {
        cerr<< "Non ci sono celle 2D" << endl;
        return false;
    }


    mesh.idCell2D.reserve(mesh.NumberCell2D);
    mesh.VerticesCell2D.reserve(mesh.NumberCell2D);
    mesh.EdgesCell2D.reserve(mesh.NumberCell2D);


    bool length_zero = false;
    for (const string& line: listLines){
        istringstream converter(line);
        unsigned int id;
        unsigned int marker;
        unsigned int NumVertic;
        unsigned int NumEdges;
        unsigned int vertice;
        unsigned int lato;
        vector<unsigned int> vertices;
        vector<unsigned int> edges;
        char delimiter;
        converter >> id >>delimiter>> marker >>delimiter>> NumVertic>>delimiter;

        vertices.resize(NumVertic);
        mesh.idCell2D.push_back(id);
        vertices.clear();
        for (unsigned int i = 0; i<NumVertic; i++){
            converter>> vertice>>delimiter;
            vertices.push_back(vertice);

        }
        mesh.VerticesCell2D.push_back(vertices);
        converter>>NumEdges>>delimiter;

        edges.resize(NumEdges);
        edges.clear();
        for (unsigned int i = 0; i<NumEdges; i++){
            converter>>lato>>delimiter;
            edges.push_back(lato);

        }

        for (unsigned int i = 0; i<size(edges)-1; i++) {
            if (norm(edges[i] - edges[i+1]) < 10*numeric_limits<double>::epsilon()){
                bool length_zero = true;
            }
        }

        mesh.EdgesCell2D.push_back(edges);

    }
    cout << "length_zero: " << (length_zero ? "true" : "false") << endl;
    return true;
}


//TEST

bool test_area(const PolygonalMesh& mesh, double tol)
{
    for (size_t i=0; i < mesh.idCell1D.size(); ++i) {

        //estrazione dell'Id dei vertici  alla fine di ogni spigolo
        int origin = mesh.VerticesCell1D[i][0];
        int end= mesh.VerticesCell1D[i][1];

        // coordinate
        double X_origin = mesh.CoordinatesCell0Ds[origin][0];
        double Y_origin = mesh.CoordinatesCell0Ds[origin][1];
        double X_end = mesh.CoordinatesCell0Ds[end][0];
        double Y_end = mesh.CoordinatesCell0Ds[end][1];

        //si verifica se lo spigolo è degenere usando tolleranza e distanza euclidea
        double d = sqrt((X_origin-X_end)*(X_origin-X_end) + (Y_origin-Y_end)*(Y_origin-Y_end));
        if(d<tol){
            cerr<<"l'area è nulla"<<endl;
            return false;
        }
        return true;
    }
}
}

























