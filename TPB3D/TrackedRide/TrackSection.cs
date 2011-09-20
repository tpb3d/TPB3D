using System;
using System.Collections.Generic;
using System.Text;
using TPB3D.Maths;
using OpenTK;

namespace TPB3D {
    class TrackSection {
        /// <summary>
        /// The track that this track section belongs too
        /// </summary>
        public Track track {
            get;
            private set;
        }

        /// <summary>
        /// The next track sections in the track
        /// </summary>
        public List<TrackSection> next {
            get;
            private set;
        }

        /// <summary>
        /// The previous track sections in the track
        /// </summary>
        public List<TrackSection> prev {
            get;
            private set;
        }

        /// <summary>
        /// The length of this track section
        /// </summary>
        public double length {
            get;
            private set;
        }

        /// <summary>
        /// The type of curve used to generate this track section (Catmull-Rom Spline, arc, or Special)
        /// </summary>
        public enum TrackCurveType {
            Spline,
            Arc,
            Special
        };

        /// <summary>
        /// The type of curve used to generate this track section (Catmull-Rom Spline, arc, or Special)
        /// </summary>
        public TrackCurveType trackCurveType {
            get;
            private set;
        }

        /// <summary>
        /// The Catmull-Rom Spline that represents this track section (if the track section curve type is spline)
        /// </summary>
        public Spline spline {
            get;
            private set;
        }

        /// <summary>
        /// The radius of this track section, in meters (if the track section curve type is arc)
        /// </summary>
        public double arcRadius {
            get;
            private set;
        }

        /// <summary>
        /// The length of this track section, in degrees (if the track section curve type is arc)
        /// </summary>
        public double arcAngle {
            get;
            private set;
        }

        /// <summary>
        /// The bank angle at the start of this track section, in degrees
        /// </summary>
        public double startingBank {
            get;
            set;
        }

        /// <summary>
        /// The bank angle at the midpoint of this track section, in degrees, may be larger than a full turn
        /// </summary>
        public double midBank {
            get;
            set;
        }

        /// <summary>
        /// The bank angle at the end of this track section, in degrees, may be larger than a full turn
        /// </summary>
        public double endingBank {
            get;
            set;
        }

        /// <summary>
        /// The speed of this track section, in meters per second
        /// If this track section is a station, this is the launch speed
        /// If this track section is a brake, this is the speed the brakes will slow the train to
        /// If this track section is a booster, this is the speed the booster will boost the train to
        /// If this track section is a lift hill, this is the speed of the chain
        /// </summary>
		public double speed { get; set; }

        /// <summary>
        /// The type of track section
        /// </summary>
        public enum TrackSectionType {
            None,
            Station,
            Brake,
            Booster,
            LiftHill,
            Special
        }

        public TrackSectionType trackSectionType { get; set; }

        /// <summary>
        /// Generates the 3D model for this track section
        /// </summary>
        public double GenerateModel(double startlength) {
            // unimplemented
            return startlength;
        }
    	
		public void Draw()
		{
			throw new NotImplementedException();
		}
    }
}
