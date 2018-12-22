#ifndef __CELL_MACHINE__
#define __CELL_MACHINE__
/*
 * =====================================================================================
 *
 *       Filename:  CellMachine.hpp
 *
 *    Description:  CellMachine is designed for handling the Voronoi cell of a single
 *                  particle surrounded by certain particles.
 *
 *        Version:  1.0
 *        Created:  12/22/2018
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhswee (zhswee@gmail.com)
 *   Organization: South China University of Technology
 *
 * =====================================================================================
 */
 #include <iostream>
 #include <fstream>
 #include <map>
 //#include "process.hpp"
 #include <limits>
 #include <cmath>
 #include <sys/stat.h>
 #include "include.hpp"
 #include "fileloader.hpp"
 #include "pointpattern.hpp"
 #include "duplicationremover.hpp"
 #include "polywriter.hpp"
 #include "postprocessing.hpp"
 #include "csplitstring.hpp"
 #include "parAttr.hpp"

class CellMachine{//this class is designed to handle the computation of a single particle's cell.
private:
  //configuration
	std::string in_folder;//folder for input data
  std::string out_folder;//folder for output data
	int nx, ny, nz;
  double xmin,xmax,ymin,ymax,zmin,zmax;//box size
  double wall_xmin,wall_xmax,wall_ymin,wall_ymax,wall_zmin,wall_zmax;//the global wall size
  bool xpbc, ypbc,zpbc;
	bool savereduced, removeduplicate, withboundary, savevtk, cellVTK, savepov, savepoly;
	voro::container *con;//container
  unsigned long long pid;//point id
  //std::map < unsigned long long, int> labelidmap;//no need to use map, just vector is ok
  std::vector<int> labelidmap;
  //particleAttr pAttr;
  double rr;//resolution used to clip facets of a cell
  //cell properties
  int cid;//cell id, also particle id
  double cellVolume;
  double cellSurfaceArea;
  double cellNormalTensor[6];//six components of normalTensor(1-6)
  double cellNormalAreaTensor[6];//six components of normalAreaTensor(1-6)
public:
	CellMachine(std::string input_folder,std::string output_folder);
	~CellMachine(){
    if(con){
      con->clear();
      delete con;
    }
  };
	void pushPoints(particleAttr& pAttr);//push points to the box for voronoi tessellation
	void writeGlobal();//write data to files with info from all particles
	void writeLocal(polywriter *pw);//write data to files with info from just this particle
	void processing();
  void getFaceVerticesOfFace( std::vector<int>& f, unsigned int k, std::vector<unsigned int>& vertexList);
  void readWall(std::string filename);//read the boundar of the global wall
  void readParticle(std::string filename, bool flag, int particleId);//xyz file read
  bool isInBox(double x, double y, double z);//test if a point is inside the box
  void initial();//initialize a cell machine
  void reset();//reset the cell machine for another cell computation if needed.
};
#endif
