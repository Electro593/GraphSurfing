/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                         * 
 *  Copyright (C) 2020 Aria Seiler                                       * 
 *                                                                         * 
 *  This program is free software: you can redistribute it and/or modify   * 
 *  it under the terms of the GNU General Public License as published by   * 
 *  the Free Software Foundation, either version 3 of the License, or      * 
 *  (at your option) any later version.                                    * 
 *                                                                         * 
 *  This program is distributed in the hope that it will be useful,        * 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         * 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           * 
 *  GNU General Public License for more details.                           * 
 *                                                                         * 
 *  You should have received a copy of the GNU General Public License      * 
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.  * 
 *                                                                         * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PLATFORM_WIN32_LOADER_H_
#define PLATFORM_WIN32_LOADER_H_

#if 1
#   define DLL_PATH(Module) ("build/Voxarc_" Module ".dll")
#   define DLL_LOCKED_PATH(Module) ("build/Voxarc_" Module "_Locked.dll")
#else
#   define DLL_PATH(Module) ("Voxarc_" Module ".dll")
#   define DLL_LOCKED_PATH(Module) ("Voxarc_" Module "_Locked.dll")
#endif
#define DLL_LOAD_FUNC_NAME(Module) (Module "_Load")

typedef struct loader_thread_info
{
    u32 ID;
    u32 Index;
    platform_work_queue *Queue;
} loader_thread_info;

typedef struct loader_dll
{
    win32_module DLL;
    fptr LoadFunc;
    win32_filetime LastWritten;
} loader_dll;

typedef struct loader_state
{
    loader_dll GameDll;
    loader_dll UtilDll;
    win32_window Window;
    heap *Heap;
    hmem win32_raw_input *RawInput;
    v2s32 PrevCursorPos;
    v2s32 RestoreCursorPos;
    b08 CursorIsDisabled;
} loader_state;

#define PLATFORM__LOADER__FUNCS \
    /*   ReturnType                   Name                            Arguments */ \
    FUNC(void,                        Platform_CreateWorkQueueEntry,  platform_work_queue *WorkQueue, platform_work_queue_callback Function, vptr Parameter) \
    FUNC(win32_teb*,                  Platform_GetTEB,                void) \
    FUNC(win32_ldr_data_table_entry*, Platform_GetLoaderTableEntry,   u32 Index) \
    FUNC(win32_unicode_string,        Platform_GetProcessPath,        void) \
    FUNC(void,                        Platform_InitFunctions,         platform_exports *PlatformExports) \
    FUNC(win32_opengl_render_context, Platform_InitOpenGLFunctions,   platform_exports *PlatformExports, win32_device_context DeviceContext) \
    FUNC(void,                        Platform_InitKeyTables,         platform_state *PlatformState) \
    FUNC(void,                        Platform_LoadDll,               loader_dll *DllData, c08 *Path, c08 *LockedPath, c08 *LoadFuncName) \
    FUNC(void,                        Platform_UnloadDll,             loader_dll *DllData) \
    FUNC(void,                        Platform_LoadGameDll,           platform_exports *PlatformExports, util_exports *UtilExports, game_module *GameModule, loader_dll *GameDll) \
    FUNC(void,                        Platform_LoadUtilDll,           platform_exports *PlatformExports, util_module *UtilModule, loader_dll *UtilDll) \
    FUNC(void,                        Platform_UnloadGameDll,         game_module *GameModule, loader_dll *GameDll) \
    FUNC(void,                        Platform_UnloadUtilDll,         util_module *UtilModule, loader_dll *UtilDll) \
    FUNC(void,                        Platform_UpdateKeyNames,        platform_state *PlatformState) \
    FUNC(b08,                         Platform_ExecuteWorkQueueEntry, loader_thread_info *Info) \
    FUNC(win32_find_data_a,           Platform_GetFileDataA,          c08 *FileName) \
    FUNC(void,                        Platform_ClipCursor,            win32_window Window) \
    FUNC(void,                        Platform_DisableCursor,         loader_state *LoaderState, cursor_flags CursorFlags) \
    FUNC(void,                        Platform_EnableCursor,          loader_state *LoaderState, cursor_flags CursorFlags) \
    FUNC(void,                        Platform_ProcessMessages,       platform_state *PlatformState) \
    FUNC(u32 _API_ENTRY,              Platform_ThreadCallback,        vptr Parameter) \
    FUNC(s64 _API_ENTRY,              Platform_WindowCallback,        win32_window Window, u32 Message, u64 WParam, s64 LParam) \

#endif