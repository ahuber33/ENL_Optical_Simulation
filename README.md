# ENL_Optical_Sim for Studies of light detectors [huber@ecnbg.in2p3.fr, huberarnaud@gmail.com]

# INSTRUCTIONS TO USE THE SIMULATION
# - Download the VMWare Geant4.11.0.0 from https://heberge.lp2ib.in2p3.fr/G4VM/index.html
# - Copy all the files from ENL_Optical_Simulation folder (https://github.com/ahuber33/ENL_Optical_Simulation)
# - Create a build folder in the ENL_Optical_Simulation folder and go inside.
# - Use this command : "cmake -DGeant4_DIR=$G4COMP ../" and compile it with make
# - The executable ENLOpticalSim will be add to your bin folder
# - If you want to have a visualization, launch this command : "./ENLOpticalSim [name of ROOT file ]". It will generate 1 particle according to the vis.mac with QT and you will have a ROOT file with the name you gave in response located in the Resultats folder.
# - If you want to have statistics without the visualization, use this command : "./ENLOpticalSim [name of ROOT file] [number of events generated] [name of macro]". Personnaly, I used the vrml.mac but you can create another one. Just to remember that you need to write the name of your macro when you launch the simulation.
# - If you want to change the geometry (HPD to PMT or something else), you just need to choose the correct geometryfile.cc in the CMakeLists.cc. Don't forget to comment the other one.
# - You can change the lighyield in the Materials.cfg located in the bin folder without re-compile the code.
# - DO NOT HESITATE TO REPORT BUGS OR ANY IDEAS THAT WILL IMPROVE THE SIMULATION !!!!
#- For information :
#   - Scintillation properties are defined in the ENLOpticalSimMaterials.cc
#   - Index or length attenuation are defined in the ENLOpticalSimMaterials.cc
#   - All the reflectors & PMT properties are defined in the ENLOpticalGeometryxxx.cc used.
#   - theRunTree corresponds to general optical datas from 1 event (number of photons generated, ect)
#   - theRunTree_bis corresponds to information attached to all single photons created. Be careful if you launch big simulations because the ROOT file will be fat... Don't hesitate to comment the "runac->UpdateStatisticsbis(Statisticsbis);" in the ENLOpticalSimEventAction.cc if you don't need these informations
#   - Tree_electrons corresponds to basic information about electrons as a primary particle.

#commit #1 le 07/03/2022 (First commit)
# - Simulation issue  du commit #5 de TPSim avec nettoyage pour simplifier la lecture du code

#commit #2 le 07/03/2022 (additional commit)
# - Ajout de l'information sur l'??nergie du photo??lectrons cr??e ?? la photocathode dans le RunTreeBis au niveau de la d??tection.
# - Ajout des commentaires n??cessaires ?? l'installation et ?? l'utilisation de la simulation au d??but de ce fichier.

#commit #3 le 08/03/2022 (Split absorption/scattering length)
# - Ajout de la propri??t?? Rayleigh scattering et donc split de l'attenuation length en absorption length et scattering length selon [https://www.researchgate.net/publication/254060762_Optical_Absorption_Length_Scattering_Length_and_Refractive_Index_of_LaBr3Ce3]
# - Selon cette r??f??rence, l'absorption entraine quasi ?? chaque fois la r????mission d'un photon derri??re donc ?? investiguer dans le futur !!!
# -> commit 3 bis r??tablit juste certains commentaires pour ??viter de polluer l'affichage lors de la simulation
# -> commit 3 ter est juste un mini patch r??solvant un petit soucis dans l'obtention des r??sultats
