﻿// -----------------------------------------------------------------------------
// <copyright file="ErrorCode.cs" company="Microsoft Corporation">
//     Copyright (c) Microsoft Corporation. Licensed under the MIT License.
// </copyright>
// -----------------------------------------------------------------------------

namespace Microsoft.WinGet.Client.Common
{
    /// <summary>
    /// Error code constants.
    /// </summary>
    public class ErrorCode
    {
        /// <summary>
        /// Error code for ERROR_FILE_NOT_FOUND.
        /// </summary>
        public const int FileNotFound = unchecked((int)0x80070002);
    }
}
