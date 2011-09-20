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

namespace OOGL.Animation
{
	/// <summary>
	/// Animation controller used in skeletal animation
	/// <remarks>Thread safety - This class is thread safe.</remarks>
	/// </summary>
	public class Controller
	{
        private Track[] tracks;
		private readonly Sample[] samples;

        public Controller(Model model)
        {
			this.samples = model.samples;
			
            if (this.samples != null && this.samples.Length > 0)
            {
                this.tracks = new Track[] { new Track(this.samples[0]) };
            }
            else
            {
                this.tracks = new Track[0];
            }
        }

        public Track CrossfadeTo(string sampleName, float fadeDuration)
        {
            Track fadeTo = AddTrack(sampleName);

            foreach (var track in Tracks)
            {
                track.FadeDuration = fadeDuration;

                if (track.sample.name == sampleName)
                {
                    if (track.FadeIn == false)
                    {
                        track.Reset();
                        track.FadeIn = true;
                        track.Weight = 0;
                    }
                }
                else
                {
                    track.FadeOut = true;
                }
            }

            return fadeTo;
        }

        public Track CrossfadeTo(string sampleName)
        {
            Track fadeTo = AddTrack(sampleName);
            float fadeDuration = (fadeTo.sample.endTime - fadeTo.sample.startTime) / 0.75f;

            foreach (var track in Tracks)
            {
                track.FadeDuration = fadeDuration;

                if (track.sample.name == sampleName)
                {
                    if (track.FadeIn == false)
                    {
                        track.Reset();
                        track.FadeIn = true;
                        track.Weight = 0;
                    }
                }
                else
                {
                    track.FadeOut = true;
                }
            }
            
            return fadeTo;
        }

        public Track AddTrack(string sampleName)
        {
            Track track = FindSample(sampleName);
            if (track != null) return track;

            track = new Track(Sample.FindSample(this.samples, sampleName));

            List<Track> tracks = new List<Track>(this.tracks);
            tracks.Add(track);
            this.tracks = tracks.ToArray();

            return track;
        }

        public void RemoveTrack(string sampleName)
        {
            List<Track> tracks = new List<Track>(this.tracks);
            for (int i = tracks.Count - 1; i >= 0; i--)
            {
                if (tracks[i].sample.name == sampleName) tracks.RemoveAt(i);
            }
            this.tracks = tracks.ToArray();
        }

        public Track FindSample(string sampleName)
        {
            foreach (var track in this.tracks)
            {
                if (track.sample.name == sampleName) return track;                
            }
            return null;
        }

        public Track[] Tracks
        {
            get
            {
                return this.tracks;
            }
        }

        public void Update(float elapsedTime)
        {
            foreach (Track track in this.tracks)
            {
                track.Update(elapsedTime);
                if (track.FadeOut && track.Weight <= 0) RemoveTrack(track.sample.name);
            }
        }   
	}
}
