{ 
   TControlBar bar("vertical", "Main Bar", 0, 0);
   bar.SetFont("-adobe-helvetica-bold-r-*-*-24-*-*-*-*-*-iso8859-1");

   bar.AddButton("Help to run demos",".x demoshelp.C",
                 "Explains how to run the demos");
   
   bar.AddButton("Analyse file", "analyse()",
                 "Analysing some file");

   bar.AddButton("Angles of shoot", ".x macros/DrawEvents.C",
                 "Analysing some file");

   bar.AddButton("Cut and Fit spectrum", ".x macros/FitAll.C",
                  "cut backgounds");
                 
   bar.AddButton("#Delta E", ".x macros/DrawDeltaE.C",
                 "Draw Delta E");

   bar.AddButton("Draw Crystals",".x macros/DrawLYSO.C",
                 "display detecot information");

   bar.AddButton("Draw DeltaE vs E",".x macros/DrawDeltaEvsE.C",
                 "DeltaE vs E");

   bar.AddButton("Draw All", ".x macros/DrawAll.C",
                 "Draw all");

   bar.AddButton("Count asymmetry", ".x macros/CountPol.C",
                 "Visualize Asimmetry");

   bar.AddButton("save results", ".x macros/SaveAll.C", 
                  "Draw all");
                  
   bar.AddButton("Close ROOT", "gSystem->Exit(1)",
                 "Close ControlBar");

   bar.Show();
   gROOT->SaveContext();
}
