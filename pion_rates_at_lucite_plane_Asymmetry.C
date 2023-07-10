// Run using (for example):
//   build/reroot -l -q 'analysis/pion/pion_rates_at_lucite_plane.C("pion_rates_at_lucite_plane_evgen_pion_1k.root")'
void pion_rates_at_lucite_plane_Asymmetry(const TString& files)
{
  TChain* T = new TChain("T");
  T->Add(files);
  Double_t pi = 3.14159265358979323846;  
  Double_t rate = 0;
  std::vector<remollEventParticle_t>* parts = 0;
  std::vector<remollGenericDetectorHit_t>* hits = 0;
  remollEvent_t* ev=0;

  T->SetBranchAddress("rate", &rate);
  T->SetBranchAddress("hit", &hits);
  T->SetBranchAddress("part", &parts);
  T->SetBranchAddress("ev", &ev);


//loop over azimuthal angle

  for (double ph = -pi-(pi/28); ph <= pi-(pi/28); ph += 2*pi/28) {

    TH1F hph8000(Form("hph8001_%.0f", ph), "hits in phi", 100, -100, 0);

      for (size_t iev = 0; iev < T->GetEntries(); iev++) {
        T->GetEntry(iev);

      double asym = ev->A;

        for (size_t ihit = 0; ihit < hits->size(); ihit++) {
          remollGenericDetectorHit_t hit = hits->at(ihit);

            if (hit.ph > ph && hit.ph < ph+2*pi/28) {
//          hph8000.Fill(asym, rate/4.25e12);
          hph8000.Fill(asym);
      }
     }
    }
            double mean = 0;
            double std_dev = 0;
            mean = hph8000.GetMean();
            std_dev = hph8000.GetStdDev();
   
            cout << "phi = " << (ph+(ph+(2*pi/28)))/2 << ",MaxBinContent = " << mean << "/" << std_dev << endl;
  }
 }
