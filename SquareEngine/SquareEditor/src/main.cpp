#include <EditorLayer.h>

static int Application(int argc, char** argv)
{
    EditorLayer editorLayer = EditorLayer(argc, argv);
    editorLayer.Run();

    return 0;
}

#include <EntryPoint.h>