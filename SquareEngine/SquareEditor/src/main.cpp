#include <EditorLayer.h>

int Application(int argc, char** argv)
{
    EditorLayer editorLayer = EditorLayer();
    editorLayer.Run(argc, argv);

    return 0;
}

#include <EntryPoint.h>