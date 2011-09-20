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
	/// Animation sequencing track used in skeletal animation
	/// <remarks>Thread safety - This class is thread safe.</remarks>
	/// </summary>	
    public class Track
    {
        public readonly Sample sample;

        public Track(Sample sample)
        {
            if (sample == null) throw new ArgumentNullException();
            this.sample = sample;

            Reset();
        }

        private float time = 0;
        public float Time
        {
            get
            {
                return this.time;
            }
        }

        private float speed = 1;
        public float Speed
        {
            get
            {
                return this.speed;
            }
            set
            {
                if (value < 0) value = 0;
                this.speed = value;
            }
        }

        private float weight = 1;
        public float Weight
        {
            get
            {
                return weight;
            }
            set
            {
                if (value < 0) value = 0;
                if (value > 1) value = 1;

                weight = value;
            }
        }

        private bool fadeIn = false;
        public bool FadeIn
        {
            get
            {
                return fadeIn;
            }
            set
            {
                if (value) fadeOut = false;
                fadeIn = value;
            }
        }

        private bool fadeOut = false;
        public bool FadeOut
        {
            get
            {
                return fadeOut;
            }
            set
            {
                if (value) fadeIn = false;
                fadeOut = value;
            }
        }

        private float fadeDuration = 1;
        public float FadeDuration
        {
            get
            {
                return fadeDuration;
            }
            set
            {
                if (value < 0) value = 0;
                fadeDuration = value;
            }
        }

        public void Reset()
        {
            fadeIn = false;
            fadeOut = false;

            switch (sample.playMode)
            {
                case Sample.PlayMode.forwardLooping:
                case Sample.PlayMode.forwardOnce:
                {
                    this.time = sample.startTime;
                }
                break;

                case Sample.PlayMode.backwardLooping:
                case Sample.PlayMode.backwardOnce:
                {
                    this.time = sample.endTime;
                }
                break;

                default: throw new InvalidOperationException();
            }
        }

        public void Update(float elapsedTime)
        {
            float adjustedTime = elapsedTime * speed;

            switch (sample.playMode)
            {
                case Sample.PlayMode.forwardLooping:
                {
                    this.time += adjustedTime;
                    float overage = time - sample.endTime;
                    if (overage > 0) this.time = sample.startTime + overage;
                }
                break;

                case Sample.PlayMode.forwardOnce:
                {
                    this.time += adjustedTime;
                    if (this.time > sample.endTime) this.time = sample.endTime;
                }
                break;

                case Sample.PlayMode.backwardLooping:
                {
                    this.time -= adjustedTime;
                    float underage = sample.startTime - time;
                    if (underage < 0) this.time = sample.endTime - underage;
                }
                break;

                case Sample.PlayMode.backwardOnce:
                {
                    this.time -= adjustedTime;
                    if (this.time < sample.startTime) this.time = sample.startTime;
                }
                break;

                default: throw new InvalidOperationException();
            }

            if (fadeIn && Weight < 1)
            {
                if (fadeDuration > 0)
                {
                    float weight = Weight;
//                    float deltaWeight = (elapsedTime / fadeDuration) * (1 - weight);
                    float deltaWeight = elapsedTime / fadeDuration;
                    Weight = weight + deltaWeight;
                }
                else
                {
                    Weight = 1;
                }
            }

            if (fadeOut && Weight > 0)
            {
                if (fadeDuration > 0)
                {
                    float weight = Weight;
//                    float deltaWeight = (elapsedTime / fadeDuration) * (weight);
                    float deltaWeight = elapsedTime / fadeDuration;
                    Weight = weight - deltaWeight;
                }
                else
                {
                    Weight = 0;
                }
            }
        }   
    }
}