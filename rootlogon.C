{
	cout << "mari gamarjoba" << endl;
	Char_t szLofMod[] = "analyse_C.so";
	if( gSystem->Load(szLofMod) )
		std::cout << Form("\n ERROR loaded %s\n", szLofMod);

	gROOT->Macro("macros/Buttons.C");
}
