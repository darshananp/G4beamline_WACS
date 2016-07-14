{
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  gStyle->SetTitleSize(0.05,"X");
  gStyle->SetTitleSize(0.05,"Y");

  //param FZDX=17.66*$INCH*10
  double FZDY=30.74*2.54;
  double FZDZ=76.34*2.54;

  double FZBCoilX=2*0.925*2.54;
  double FZBCoilY=FZDY-2*5.98*2.54;
  double FZBCoilZ=FZDZ+2.62*2.54+3.35*2*2.54;
  double CoilThick=18.5/2.0;
  double FZBCoilY=FZDY-2*5.98*2.54;
  TCanvas *cc = new TCanvas("cc","",200,10,700,900);
  //  TFile f("WACS_8800_DeflElecBeamPipe.root");
  TFile f("WACS_8800.0.1.rl.10000.ev.root");

  VirtualDetector->cd();
  CoilPlane1->SetAlias("e","sqrt(Px**2+Py**2+Pz**2)");
  CoilPlane2->SetAlias("e","sqrt(Px**2+Py**2+Pz**2)");

  cc->Divide(1,2);
  cc->cd(1);
  CoilPlane1->Draw("y/10:z/10+531.4>>h1(240,-120,120,100,-50,50)","","colz");
  h1->GetXaxis()->SetTitle("Z coordinate [cm]");
  h1->GetYaxis()->SetTitle("Y coordinate [cm]");
  h1->SetTitle("Left Coil");
  h1->Draw("colz");
  TLine l1( -FZDZ/2.0 , FZDY/2.0 , FZDZ/2.0 , FZDY/2.0 );
  l1.Draw();
  l1.SetLineWidth(3);
  TLine l2( -FZDZ/2.0 , -FZDY/2.0 , FZDZ/2.0 , -FZDY/2.0 );
  l2.Draw();
  l2.SetLineWidth(3);
  TLine l3( -FZDZ/2.0 , -FZDY/2.0 , -FZDZ/2.0 , FZDY/2.0 );
  l3.Draw();
  l3.SetLineWidth(3);
  TLine l4( FZDZ/2.0 , -FZDY/2.0 , FZDZ/2.0 , FZDY/2.0 );
  l4.Draw();
  l4.SetLineWidth(3);

  TLine l5( -FZBCoilZ/2.0 , FZBCoilY/2.0 , FZBCoilZ/2.0 , FZBCoilY/2.0 );
  l5.SetLineWidth(3);
  l5->SetLineColor(2);
  l5.Draw();
  TLine l6( -FZBCoilZ/2.0 , -FZBCoilY/2.0 , FZBCoilZ/2.0 , -FZBCoilY/2.0 );
  l6.SetLineWidth(3);
  l6->SetLineColor(2);
  l6.Draw();
  TLine l7( -FZBCoilZ/2.0 , -FZBCoilY/2.0 , -FZBCoilZ/2.0 , FZBCoilY/2.0 );
  l7.SetLineWidth(3);
  l7->SetLineColor(2);
  l7.Draw();
  TLine l8( FZBCoilZ/2.0 , -FZBCoilY/2.0 , FZBCoilZ/2.0 , FZBCoilY/2.0 );
  l8.SetLineWidth(3);
  l8->SetLineColor(2);
  l8.Draw();

  TLine l9( -FZBCoilZ/2.0+CoilThick , FZBCoilY/2.0-CoilThick , FZBCoilZ/2.0-CoilThick , FZBCoilY/2.0-CoilThick );
  l9.SetLineWidth(3);
  l9->SetLineColor(2);
  l9.Draw();

  TLine l10( -FZBCoilZ/2.0+CoilThick , -FZBCoilY/2.0+CoilThick , FZBCoilZ/2.0-CoilThick , -FZBCoilY/2.0+CoilThick );
  l10.SetLineWidth(3);
  l10->SetLineColor(2);
  l10.Draw();


  TLine l11( -FZBCoilZ/2.0+CoilThick , -FZBCoilY/2.0+CoilThick , -FZBCoilZ/2.0+CoilThick , FZBCoilY/2.0-CoilThick );
  l11.SetLineWidth(3);
  l11->SetLineColor(2);
  l11.Draw();

  TLine l12( FZBCoilZ/2.0-CoilThick , -FZBCoilY/2.0+CoilThick , FZBCoilZ/2.0-CoilThick , FZBCoilY/2.0-CoilThick );
  l12.SetLineWidth(3);
  l12->SetLineColor(2);
  l12.Draw();


  cc->cd(2);
  CoilPlane2->Draw("y/10:z/10+531.4>>h2(240,-120,120,100,-50,50)","e","colz");
  h2->GetXaxis()->SetTitle("Z coordinate [cm]");
  h2->GetYaxis()->SetTitle("Y coordinate [cm]");
  h2->SetTitle("Right Coil");
  h2->Draw("colz");

  l1.Draw();
  l2.Draw();
  l3.Draw();
  l4.Draw();

  l5.Draw();
  l6.Draw();
  l7.Draw();
  l8.Draw();

  l9.Draw();
  l10.Draw();
  l11.Draw();
  l12.Draw();

  cc->Print("Coil_hit.gif");
  cc->Print("Coil_hit.pdf");
  cc->Print("Coil_hit.eps");

}
