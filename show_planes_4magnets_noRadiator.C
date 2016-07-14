{
  gStyle->SetOptFit(1);
  //  gStyle->SetOptStat(0);
  gStyle->SetNdivisions(505,"X");

  gStyle->SetTitleSize(0.05,"X");
  gStyle->SetTitleSize(0.05,"Y");


  TCanvas *cc = new TCanvas("cc","",200,10,700,900);
  cc->Divide(1,2);
  cc->Draw();
  TFile f("WACS_8800_planes_4magnets_noRadiator.root");

  double Zpos[] = { 670, 690, 710, 730, 750, 770, 790, 810, 830, 850, 870, 890, 910, 930, 950, 970, 990, 1010,
		    1030, 1050, 1070, 1090, 1110, 1130, 1150, 1170, 1190, 1210, 1230, 1250 ,
		    1270, 1290, 1310, 1330, 1350, 1370, 1390, 1410, 1430, 1450 };

  double Xpos[40];
  double Ypos[40];
  double XposSig[40];
  double YposSig[40];

  VirtualDetector->cd();
  TIter next(gDirectory->GetListOfKeys());
  TH1F *hx=new TH1F("hx","Electron x ",100,-15,15);
  TH1F *hy=new TH1F("hy","Electron y ",4000,-300,100);
  cc->cd(1);
  hx->Draw();
  cc->Update();
  getchar();

  TKey* key;
  int ii=0;
  while ((key = (TKey*) next())) 
    {
      TNtuple* plane = (TNtuple*) key->ReadObj();
      TString str( plane->GetName() );
      if( str.BeginsWith("Plane") )
	{
	  plane->SetAlias("e","(sqrt(Px**2+Py**2+Pz**2)+0.51**2)/1000.0");
	  plane->SetAlias("tang","-Py/Pz");
	  plane->SetAlias("cosalpha","1./sqrt(1+tang**2)");
	  cout << str << endl;
	  plane->Draw("x/10.0>>hx","ParentID==0","goff");
	  //	  plane->Draw("y/10.0*cosalpha>>hy","ParentID==0&&e>4","goff");
	  plane->Draw("y/10.0>>hy","ParentID==0&&e>8","goff");
	  int nn = hy->GetMaximumBin();
	  double ymax=hy->GetBinCenter(nn);
	  nn = hx->GetMaximumBin();
	  double xmax=hx->GetBinCenter(nn);
	  cout << xmax << "  " << ymax << endl;
	  cc->cd(1);
	  hx->Draw();
	  cc->cd(2);
	  hy->Draw();

	  hy->SetTitle(str);
	  hy->GetXaxis()->SetRangeUser( ymax-3 , ymax+3);
	 	  
	  double rmsX = hx->GetRMS();
	  double rmsY = hy->GetRMS();

	  //	  hx->Fit("gaus","","",-2*rmsX,3*rmsX);
	  //	  hy->Fit("gaus","","",ymax-2*rmsY,ymax+2*rmsY);


	  Xpos[ii]    = hx->GetMean();
	  Ypos[ii]    = hy->GetMean();
	  XposSig[ii] = hx->GetMean();
	  YposSig[ii] = hy->GetMean();

	  cc->Modified();
	  cc->Update();
	  cc->Update();
	  //	  getchar();
	  hy->GetXaxis()->UnZoom();
	  ii++;
	}
    }
  TGraphErrors *grX = new TGraphErrors(40, Zpos , Xpos );
  grX->SetMarkerStyle(20);
  grX->SetTitle("Defelcted beam position vs Z");
  grX->GetXaxis()->SetTitle("Z position [cm]");
  grX->GetYaxis()->SetTitle("X position [cm]");

  TGraphErrors *grY = new TGraphErrors(40, Zpos , Ypos );
  grY->SetMarkerStyle(20);
  grY->SetTitle("Defelcted beam position vs Z");
  grY->GetXaxis()->SetTitle("Z position [cm]");
  grY->GetYaxis()->SetTitle("Y position [cm]");
  grY->Fit("pol1");
  TF1 *fp1 = grY->GetFunction("pol1");
  cout << "Exit dipole Y= " << fp1->Eval(-431.4) << endl;

  TGraphErrors *grXsig = new TGraphErrors(40, Zpos , XposSig );
  grXsig->SetMarkerStyle(20);
  grXsig->SetTitle("Defelcted beam sigma vs Z");
  grXsig->GetXaxis()->SetTitle("Z position [cm]");
  grXsig->GetYaxis()->SetTitle("Sigma_{x} [cm]");
  

  TGraphErrors *grYsig = new TGraphErrors(40, Zpos , YposSig );
  grYsig->SetMarkerStyle(20);
  grYsig->SetTitle("Defelcted beam sigma vs Z");
  grYsig->GetXaxis()->SetTitle("Z position [cm]");
  grYsig->GetYaxis()->SetTitle("Sigma_{y} [cm]");

  TCanvas *cc1 = new TCanvas("cc1", "", 200 ,10 , 900 , 900 );
  cc1->Divide(2,2);
  cc1->GetPad(1)->SetGridx();
  cc1->GetPad(1)->SetGridy();

  cc1->GetPad(2)->SetGridx();
  cc1->GetPad(2)->SetGridy();

  cc1->GetPad(3)->SetGridx();
  cc1->GetPad(3)->SetGridy();

  cc1->GetPad(4)->SetGridx();
  cc1->GetPad(4)->SetGridy();

  cc1->cd(1);
  grX->Draw("AP");
  cc1->cd(2);
  grY->Draw("AP");
  cc1->cd(3);
  grXsig->Draw("AP");
  cc1->cd(4);
  grYsig->Draw("AP");

  cc1->Print("beam_position_and_size_vsZ_4magnets.gif");
}
