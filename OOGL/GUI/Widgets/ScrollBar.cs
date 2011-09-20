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
using System.Drawing;

using OpenTK.Graphics;
using OpenTK;
using OpenTK.Input;

using OOGL.GUI.Abstract;

namespace OOGL.GUI.Widgets
{
    public abstract class ScrollBar : BaseControl
    {
        protected Rectangle screenRectValueButton = new Rectangle();
        protected Rectangle screenRectDecreaseValueButton = new Rectangle();
        protected Rectangle screenRectIncreaseValueButton = new Rectangle();
        protected Rectangle screenRectScrollRange = new Rectangle();

        public ScrollBar(BaseFrameMgr frameMgr, BaseControl parent)
            : base(frameMgr, parent)
        {

        }

        protected int buttonSize = 10;
        public int ButtonSize
        {
            get
            {
                return buttonSize;
            }
        }

        protected int value = 0;
        public int Value
        {
            get
            {
                return value;
            }
            set
            {
                if (value < minValue) return;
                if (value > maxValue) return;
                this.value = value;
                OnValueChanged();
                NeedUpdate();
            }
        }

        protected int minValue = 0;
        public int MinValue
        {
            get
            {
                return minValue;
            }
            set
            {
                if (value >= maxValue) return;
                minValue = value;
                if (Value < minValue) Value = minValue;
                NeedUpdate();
            }
        }

        protected int maxValue = 100;
        public int MaxValue
        {
            get
            {
                return maxValue;
            }
            set
            {
                if (value <= minValue) return;
                maxValue = value;
                if (Value > maxValue) Value = maxValue;
                NeedUpdate();
            }
        }

        protected int smallChange = 1;
        public int SmallChange
        {
            get
            {
                return smallChange;
            }
            set
            {
                smallChange = value;
            }
        }

        protected int largeChange = 10;
        public int LargeChange
        {
            get
            {
                return largeChange;
            }
            set
            {
                largeChange = value;
            }
        }

        public event EventHandler ValueChanged;
        protected void OnValueChanged()
        {
            EventHandler items = ValueChanged;
            if (items == null) return;
            items(this, null);
        }

        protected bool dragging = false;
        public override bool OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            if (screenRectDecreaseValueButton.Contains(e.X, e.Y))
            {
                Value--;
            }

            if (screenRectIncreaseValueButton.Contains(e.X, e.Y))
            {
                Value++;
            }

            if (screenRectValueButton.Contains(e.X, e.Y))
            {
                dragging = true;
            }

            return base.OnMouseDown(sender, e);
        }
    }
}
