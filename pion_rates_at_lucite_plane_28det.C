// Run using (for example):
//   build/reroot -l -q 'analysis/pion/pion_rates_at_lucite_plane.C("pion_rates_at_lucite_plane_evgen_pion_1k.root")'
void pion_rates_at_lucite_plane_plot(const TString& files)
{
  TChain* T = new TChain("T");
  T->Add(files);
  Double_t pi = 3.14159265358979323846;  
  Double_t rate = 0;
  std::vector<remollEventParticle_t>* parts = 0;
  std::vector<remollGenericDetectorHit_t>* hits = 0;

  T->SetBranchAddress("rate", &rate);
  T->SetBranchAddress("hit", &hits);
  T->SetBranchAddress("part", &parts);

// Create a histograms for 28 detectors

TH1D *hDetMax = new TH1D("hDetMax", "hDetMax", 28, 1, 29);

  double detMax = 0.0;

//loop over azimutal angle

  for (double ph = -pi-(pi/28); ph <= pi-(pi/28); ph += 2*pi/28) {

    TH1F hph8001(Form("hph8001_%.0f", ph), "hits in phi", 10, 0, 10);

      for (size_t iev = 0; iev < T->GetEntries(); iev++) {
        T->GetEntry(iev);

        for (size_t ihit = 0; ihit < hits->size(); ihit++) {
          remollGenericDetectorHit_t hit = hits->at(ihit);

          if (hit.det == 8001 && hit.p > 2*MeV && hit.ph > ph && hit.ph < ph+2*pi/28 &&
              (hit.pid == 11 || hit.pid == -11 || hit.pid == 211 || hit.pid == -211 || hit.pid == 13 || hit.pid == -13)) {
//            if (hit.det == 8000 && hit.ph > ph && hit.ph < ph+2*pi/28) {
            hph8001.Fill(1, rate/4.25e12);
          }
	}
      }
       cout << "phi = " << (ph+(ph+(2*pi/28)))/2 << ",MaxBinContent = " << hph8001.GetBinContent(hph8001.GetMaximumBin()) << "/" << hph8001.GetBinError(hph8001.GetMaximumBin()) << endl;
       detMax = hph8001.GetBinContent(hph8001.GetMaximumBin());
       double maxBinContent = hph8001.GetMaximum();
  
 }
}
