#include "TextReader.h"
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

TextReader::TextReader(){
	obj = new ObjReader();
}

TextReader::~TextReader(){

}

void TextReader::parse(Scene& scene, const char* file_loc){
	std::ifstream file;
	file.open(file_loc);
	std::string line;

	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	int sp = 1;
	glm::vec3 kr;

	Transform* trans = new Transform();
	bool is_transformed = false;

	while(std::getline(file, line)){
		std::stringstream l(line);
		char type[10];
		l >> type;

		if(strcmp(type, "cam") == 0){
			float x, y, z;
			float llx, lly, llz;
			float lrx, lry, lrz;
			float ulx, uly, ulz;
			float urx, ury, urz;

			l >> x, l >> y, l >> z;
			l >> llx, l >> lly, l >> llz;
			l >> lrx, l >> lry, l >> lrz;
			l >> ulx, l >> uly, l >> ulz;
			l >> urx, l >> ury, l >> urz;

			Camera* cam = new Camera(x, y, z, llx, lly, llz, lrx, lry, lrz, ulx, uly, ulz, urx, ury, urz);
			scene.defineCamera(cam);
		} else if(strcmp(type, "sph") == 0){
			float x, y, z;
			float r;

			l >> x, l >> y, l >> z;
			l >> r;

			Sphere* s = new Sphere(x, y, z, r);
			s->setAmbient(ka);
			s->setDiffuse(kd);
			s->setSpecular(ks);
			s->setSpecularPow(sp);
			s->setReflect(kr);

			if(is_transformed){
				s->setTransform(trans->getTransform());
			}

			scene.insertSphere(s);
		} else if(strcmp(type, "tri") == 0){
			float v1x, v1y, v1z;
			float v2x, v2y, v2z;
			float v3x, v3y, v3z;
			
			l >> v1x, l >> v1y, l >> v1z;
			l >> v2x, l >> v2y, l >> v2z;
			l >> v3x, l >> v3y, l >> v3z;

			Triangle* tri = new Triangle(v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z);
			tri->setAmbient(ka);
			tri->setDiffuse(kd);
			tri->setSpecular(ks);
			tri->setSpecularPow(sp);
			tri->setReflect(kr);

			if(is_transformed){
				tri->setTransform(trans->getTransform());
			}

			scene.insertTriangle(tri);
		} else if(strcmp(type, "obj") == 0){
			std::string loc;

			l >> loc;

			if(l.eof()){
				obj->parse(loc.c_str(), 1);
			} else{
				int f_type;

				l >> f_type;

				obj->parse(loc.c_str(), f_type);
			}

			if(is_transformed){
				obj->setTransform(trans->getTransform());
			}

			obj->createObj(scene, ka, kd, ks, sp, kr);
		} else if(strcmp(type, "ltp") == 0){
			float x, y, z;
			float r, g, b;
			int f;

			PointLight* pl;

			l >> x, l >> y, l >> z;
			l >> r, l >> g, l >> b;

			if(l.eof()){
				pl = new PointLight(x, y, z, r, g, b);
			} else{
				l >> f;

				pl = new PointLight(x, y, z, r, g, b, f);
			}

			scene.insertPointLight(pl);
		} else if(strcmp(type, "ltd") == 0){
			float x, y, z;
			float r, g, b;

			l >> x, l >> y, l >> z;
			l >> r, l >> g, l >> b;

			DirectionalLight* dl = new DirectionalLight(x, y, z, r, g, b);
			scene.insertDirectionalLight(dl);
		} else if(strcmp(type, "lta") == 0){
			float r, g, b;
		
			l >> r, l >> g, l >> b;

			AmbientLight* al = new AmbientLight(r, g, b);
			scene.insertAmbientLight(al);
		} else if(strcmp(type, "mat") == 0){
			float kaR, kaG, kaB;
			float kdR, kdG, kdB;
			float ksR, ksG, ksB;
			int spow;
			float krR, krG, krB;

			l >> kaR, l >> kaG, l >> kaB;
			l >> kdR, l >> kdG, l >> kdB;
			l >> ksR, l >> ksG, l >> ksB;
			l >> spow;
			l >> krR, l >> krG, l >> krB;

			ka = glm::vec3(kaR, kaG, kaB);
			kd = glm::vec3(kdR, kdG, kdB);
			ks = glm::vec3(ksR, ksG, ksB);
			sp = spow;
			kr = glm::vec3(krR, krG, krB);
		} else if(strcmp(type, "xft") == 0){
			float x, y, z;
			
			l >> x, l >> y, l >> z;

			trans->pushTranslate(x, y, z);
			is_transformed = true;
		} else if(strcmp(type, "xfr") == 0){
			float x, y, z;
			
			l >> x, l >> y, l >> z;

			trans->pushRotate(x, y, z);
			is_transformed = true;
		} else if(strcmp(type, "xfs") == 0){
			float x, y, z;
			
			l >> x, l >> y, l >> z;

			trans->pushScale(x, y, z);
			is_transformed = true;
		} else if(strcmp(type, "xfz") == 0){
			trans->resetTransform();
			is_transformed = false;
		} else {
			printf("Unknown prefix '%s' in line: %s\n", type, line.c_str());
		}
		// printf("%s\n", "Hi");
	}
	
	file.close();
}