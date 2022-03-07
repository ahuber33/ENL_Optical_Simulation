#include <iostream>
#include <fstream>

using namespace std;

void Read_spectres_CELIA()
{
  ifstream file("Spectres_CELIA.txt");
  string a;
  std::vector<float> vE, vMo, vGd, vTa;
  float E[353], Mo[353], Gd, Ta;
  double Sum;
  //file->getline();

  for (int i=0; i<353; i++)
    {
      file >> E[i] >> Mo[i] >> Gd >> Ta ;
      vE.push_back(E[i]);
      vMo.push_back(Mo[i]);
      vGd.push_back(Gd);
      vTa.push_back(Ta);
      cout << E << " " << Mo << " " << Gd << " " << Ta << endl;
      Sum += Mo[i];
    }
  file.close();


  ofstream ofile("Spectre_CELIA_Mo.txt");

  for(int i =0; i<353; i++)
    {
      ofile <<vE.at(i)/1000 << " " << vMo.at(i)/Sum << endl;
    }


  TGraph* graph = new TGraph(353, E, Mo);
  graph->Draw();

  
}
