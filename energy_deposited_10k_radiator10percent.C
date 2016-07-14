{
  ifstream fin("Power_deposit_tilted_dipole1_Radiator_10percent.txt", ios::in );
  string line;
  char name[200];
  float de_mev , de_joul;
  double nev=10000;
  double current = 1.0e-6;
  double qe = 1.60217662e-19;
  double N0=current/qe;
  double convert = N0/nev; // per second

  double total=0;
  while(!fin.eof())
    {
      getline( fin , line );
      if(line.size()==0) continue;
      if(line[0]=='#') continue;
      sscanf( line.c_str() , "%s %f %f " , &name , &de_mev , &de_joul );
      //      cout << name << "  " << de_mev << " " << de_joul << endl;
      //      cout << name << "  " << de_joul*convert << " Watts"<< endl;
      printf( "%-40s %10.3f Watts\n" , name , de_joul*convert );

      total+=de_joul*convert;
    }
  cout << "Total power deposited= " << total << " Watts" << endl;
  cout << "Beam current 1 microAmps" << endl;

}
