int Compteur(string file)
{
  TFile* f = new TFile(file.c_str());

  float a=0;
  //float Compteur=0;

  TTree *Tree = (TTree*)f->Get("Tree_electron");
  Tree->SetBranchAddress("TotalLength", &a);

  int Entries = Tree->GetEntries();
  //cout << "Entries = " << Entries << endl;

  cout << "Compteur[" << file<< "] = " << Entries << endl;

  return Entries;

}


float Mean(const char* filename, const char* TreeName, const char* VariableName)
{
  TFile* file = new TFile(filename);
  float a;
  TTree *Tree = (TTree*)file->Get(TreeName);
  Tree->SetBranchAddress(VariableName, &a);
  float Entries = Tree->GetEntries();
  float Mean=0;
  float Sum=0;

  for(int i=0; i<Entries; i++)
  {
    Tree->GetEntry(i);
    Sum+=a;
  }

  Mean= Sum/Entries;
  
  cout << "Mean[" << filename << "/" << VariableName << "] = " << Mean << endl;

  file->Close();

  return Mean;
}

float Sigma(const char* filename, const char* TreeName, const char* VariableName, float Mean)
{
  TFile* file = new TFile(filename);
  float a;
  TTree *Tree = (TTree*)file->Get(TreeName);
  Tree->SetBranchAddress(VariableName, &a);
  int Entries = Tree->GetEntries();
  float Sum=0;
  float Sigma=0;

  for(int i=0; i<Entries; i++)
  {
    Tree->GetEntry(i);
    Sigma+=pow(a-Mean, 2);
  }

  Sigma= sqrt(Sigma/Entries);

  cout << "Sigma[" << filename << "] = " << Sigma << endl;

  file->Close();

  return Sigma;
}


TGraphErrors* ge(const char* filenames[], const char* TreeName, const char* VariableName1, const char* VariableName2, const int nfiles)
{
  float x[nfiles];
  float y[nfiles];
  float e_x[nfiles];
  float e_y[nfiles];

  
  for(int i=0; i<nfiles; i++)
    {
      x[i] = Mean(filenames[i], TreeName, VariableName1); //conv keV to MeV
      y[i] = Mean(filenames[i], TreeName, VariableName2); //conv mm to cm
      e_x[i]=0;
      e_y[i] = Sigma(filenames[i], TreeName, VariableName2, y[i]); //conv mm to cm
      x[i] = x[i]/1000;
      y[i] = y[i]/10;
      e_y[i] = e_y[i]/10;
      cout << "x[" << i << "] = " << x[i] << endl;
      cout << "y[" << i << "] = " << y[i] << endl;
      cout << "ey[" << i << "] = " << e_y[i] << endl;
    }
  

  TGraphErrors* graph = new TGraphErrors(nfiles, x, y, e_x, e_y);
      
      
  
  //cout << "test = " << filenames[5] << endl;
  //const char* test = filenames[3];
  
  return graph;
}

vector<float> Labs(float Wavelength)
{
  TFile* file = new TFile("Study_LaBr3_attenuation.root");
  float a,b;
  vector<float> c;
  c.clear();
  TTree *Tree = (TTree*)file->Get("theRunTree_bis");
  float Entries = Tree->GetEntries();
  TH1F* h = new TH1F("h","h", 100, 0, 1000);

  for (int i=0; i<Entries; i++)
    {
      a = Tree->GetLeaf("BirthLambda")->GetValue();
      b = Tree->GetLeaf("Total_Length")->GetValue();
      Tree->GetEntry(i);
      if (a<Wavelength+0.5 && a > (Wavelength-0.5)){ h->Fill(b);}
    }

  h->Fit("expo");
  TF1* g = (TF1*)h->GetListOfFunctions()->FindObject("expo");
  c.push_back(-1/g->GetParameter(1));
  c.push_back(g->GetParError(1)/(pow(g->GetParameter(1),2)));

  //  cout << "c(1)=" << c.at(1) << endl;


  file->Close();

  return c;
  c.clear();
}

TGraphErrors* geLabs(int start, int end, int step)
{
  int n_step = (end-start)/step;
  float x[n_step];
  float y[n_step];
  float e_x[n_step];
  float e_y[n_step];
  int n=0;
  vector<float> v;
  
  for(int i=start; i<end; i+= step)
    {
      v=Labs(i);
      x[n] = i; //conv keV to MeV
      y[n] = v.at(0); //conv mm to cm
      e_x[n]=step;
      e_y[n] = v.at(1); //conv mm to cm
      n++;
      //cout << "x[" << i << "] = " << x[i] << endl;
      //cout << "y[" << i << "] = " << y[i] << endl;
      //cout << "ey[" << i << "] = " << e_y[i] << endl;
    }
  

  TGraphErrors* graph = new TGraphErrors(n_step, x, y, e_x, e_y);
      
  v.clear();
  
  //cout << "test = " << filenames[5] << endl;
  //const char* test = filenames[3];
  
  return graph;
}
