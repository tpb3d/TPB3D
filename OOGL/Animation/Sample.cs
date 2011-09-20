// Copyright (C) 2008 James P Michels III
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace OOGL.Animation
{
	/// <summary>
	/// Animation sample used in skeletal animation
	/// <remarks>Thread safety - This class is thread safe.</remarks>
	/// </summary>
    public class Sample
    {
        public enum PlayMode
        {
            forwardLooping,
            forwardOnce,
            backwardLooping,
            backwardOnce
        }

        public readonly string name;
        public readonly float startTime;
        public readonly float endTime;
        public readonly PlayMode playMode;

        private const float animationFPS = 30.0f;

        public Sample(string name, float startTime, float endTime, PlayMode playMode)
        {
            this.name = name;
            this.startTime = startTime;
            this.endTime = endTime;
            this.playMode = playMode;
        }

        public Sample(string name, int startFrame, int endFrame, PlayMode playMode)
        {
            this.name = name;
            this.startTime = (startFrame - 1) / animationFPS;
            this.endTime = (endFrame - 1) / animationFPS;
            this.playMode = playMode;
        }

        public static Sample[] Load(string fileName)
        {
            List<Sample> tracks = new List<Sample>();
            using (FileStream file = System.IO.File.OpenRead(fileName))
            {
                using (StreamReader r = new StreamReader(file))
                {
                    string line;
                    while ((line = r.ReadLine()) != null)
                    {
                        string[] cols = line.Split(',');
                        if (cols == null || cols.Length != 4) throw new FormatException();
                        string name = cols[0];
                        int startFrame = int.Parse(cols[1]);
                        int endFrame = int.Parse(cols[2]);
                        PlayMode playMode = (PlayMode)Enum.Parse(typeof(PlayMode), cols[3]);

                        tracks.Add(new Sample(name, startFrame, endFrame, playMode));
                    }
                }
            }
            return tracks.ToArray();
        }
		
		public static Sample FindSample(Sample[] samples, string name)
        {
            if (samples == null) return null;

            for (int i = 0; i < samples.Length; i++)
            {
                if (samples[i].name == name) return samples[i];
            }
            return null;
        }

    }
}
