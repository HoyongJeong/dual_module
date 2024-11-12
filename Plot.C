void Plot()
{
	//------------------------------------------------
	// Open result
	//------------------------------------------------
	TFile* file = new TFile("dual_module_2024-11-12_21-33-25.root");
	TTree* tree = (TTree*) file -> Get("dual_module");
	int proc = 0;
	int mod = 0;
	double time = 0;
	tree -> SetBranchAddress("creProcID", &proc);
	tree -> SetBranchAddress("module"   , &mod );
	tree -> SetBranchAddress("timing"   , &time);


	//------------------------------------------------
	// Histograms
	//------------------------------------------------
	TH1D* h_t1c = new TH1D("h_t1c", "Timing, 1, Cerenkov"     , 1000, 0, 100);
	TH1D* h_t1s = new TH1D("h_t1s", "Timing, 1, Scintillation", 1000, 0, 100);
	TH1D* h_t1a = new TH1D("h_t1a", "Timing, 1, All"          , 1000, 0, 100);
	TH1D* h_t2c = new TH1D("h_t2c", "Timing, 2, Cerenkov"     , 1000, 0, 100);
	TH1D* h_t2s = new TH1D("h_t2s", "Timing, 2, Scintillation", 1000, 0, 100);
	TH1D* h_t2a = new TH1D("h_t2a", "Timing, 2, All"          , 1000, 0, 100);

	h_t1c -> SetFillColor(kBlue);
	h_t1s -> SetFillColor(kBlue);
	h_t1a -> SetFillColor(kBlue);
	h_t2c -> SetFillColor(kRed);
	h_t2s -> SetFillColor(kRed);
	h_t2a -> SetFillColor(kRed);


	//------------------------------------------------
	// Fill
	//------------------------------------------------
	for ( unsigned long int i = 0; i < tree -> GetEntries(); i++ )
	{
		tree -> GetEntry(i);

		if      ( mod == 0 )
		{
			h_t1a -> Fill(time);
			if      ( proc == 0 ) h_t1c -> Fill(time);
			else if ( proc == 1 ) h_t1s -> Fill(time);
		}
		else if ( mod == 1 )
		{
			h_t2a -> Fill(time);
			if      ( proc == 0 ) h_t2c -> Fill(time);
			else if ( proc == 1 ) h_t2s -> Fill(time);
		}
	}


	//------------------------------------------------
	// Plot
	//------------------------------------------------
	TCanvas* canvas = new TCanvas("canvas", "Timing", 1800, 1440);
	canvas -> Divide(3, 3);
	canvas -> cd(1); h_t1c -> Draw();
	canvas -> cd(2); h_t1s -> Draw();
	canvas -> cd(3); h_t1a -> Draw();
	canvas -> cd(4); h_t2c -> Draw();
	canvas -> cd(5); h_t2s -> Draw();
	canvas -> cd(6); h_t2a -> Draw();
	canvas -> cd(7); h_t2c -> Draw(); h_t1c -> Draw("same");
	canvas -> cd(8); h_t2s -> Draw(); h_t1s -> Draw("same");
	canvas -> cd(9); h_t2a -> Draw(); h_t1a -> Draw("same");
}
