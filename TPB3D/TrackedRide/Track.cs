using System;
using System.Collections.Generic;
using System.Text;
using OpenTK;

namespace TPB3D {
    class Track {
        List<TrackSection> trackSections = new List<TrackSection>();
        public void Draw() {
            foreach(TrackSection trackSection in trackSections) {
                trackSection.Draw();
            }
        }
        
        public void GenerateModel() {
        	double startlength = 0;
            foreach(TrackSection trackSection in trackSections) {
                startlength = trackSection.GenerateModel(startlength);
            }
        }
    }
}
