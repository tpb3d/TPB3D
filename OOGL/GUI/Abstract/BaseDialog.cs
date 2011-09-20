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

using OpenTK.Graphics;
using OpenTK;
using OpenTK.Input;

namespace OOGL.GUI.Abstract
{
    public class BaseDialog : BaseFrame
    {
        public delegate void ResultHandlerDelegate(BaseDialog sender, bool result);

        private ResultHandlerDelegate resultHandler;

        public BaseDialog(BaseFrameMgr frameMgr, byte windowType, string name, ResultHandlerDelegate resultHandler)
            : base(frameMgr, windowType, name)
        {
            this.resultHandler = resultHandler;
        }

        protected void ReturnResult(bool result)
        {
            resultHandler(this, result);

            frameMgr.RemoveWindow(this);

            Dispose();
        }
    }
}
