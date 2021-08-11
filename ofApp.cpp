#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 3);
	this->mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh = this->mesh;
	this->line_mesh = this->mesh;

	for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {

		glm::vec3 vertex = this->draw_mesh.getVertex(i);
		//auto noise_value = ofNoise(glm::vec4(vertex * 0.003, ofGetFrameNum() * 0.005));
		auto noise_value = ofNoise(glm::vec2(i * 0.001, ofGetFrameNum() * 0.008));

		ofColor color = ofColor(239);

		if (noise_value < 0.5) {

			if (noise_value < 0.4) {

				vertex = glm::normalize(vertex) * 250; // 0 -> 250
				color = ofColor(0);
			}
			else {

				vertex = glm::normalize(vertex) * ofMap(noise_value, 0.4, 0.5, 250, 300); // 0 -> 250
				color = ofColor(ofMap(noise_value, 0.4, 0.5, 0, 239));
			}
		}

		this->draw_mesh.setVertex(i, vertex);
		this->line_mesh.setVertex(i, vertex);
		this->draw_mesh.addColor(color);

	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.37);
	ofRotateY(ofGetFrameNum() * 0.72);

	this->draw_mesh.draw();

	ofSetColor(0);
	this->line_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}