#include "ui.h"

void translator::drawUI(Attributes* attr)
{
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();

    // Ładowanie konfiguracji

    if (!attr->configValid)
        ImGui::OpenPopup("Wybór ścieżek");

    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Wybór ścieżek", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Ścieżka do folderu zawierającego słowniki");
        static std::string dictPath;
        ImGui::InputText("##dictpath", &dictPath);
        
        ImGui::Text("Ścieżka do folderu wyjściowego");
        static std::string outPath;
        ImGui::InputText("##outpath", &outPath);

        ImGui::Dummy(ImVec2(0.0f, 15.0f));
        static std::string message;
        attr->configValid = attr->wrapper.configurate(dictPath, outPath, message);
        if (ImGui::Button("Zapisz", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        {
            if (attr->configValid)
            {
                ImGui::CloseCurrentPopup();
                attr->dictsLoader = attr->wrapper.loadDicts();
            }
            else           
                ImGui::OpenPopup("Błąd");
        }

        if (ImGui::BeginPopupModal("Błąd", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text(message.c_str());
            if (ImGui::Button("Ok", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }

        ImGui::EndPopup();
    }

    //Ładowanie słowników

    if (attr->dictsLoader.joinable())
        ImGui::OpenPopup("Ładowanie słowników");

    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Ładowanie słowników", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Słownik gramatyczny");
        static float gram_progress = 0.0f;
        gram_progress = (float)attr->wrapper.getDict(0).getSize() / 4910854;
        ImGui::ProgressBar(gram_progress, ImVec2(0.0f, 0.0f));
        
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Słownik angielski");
        static float en_progress = 0.0f;
        en_progress = (float)attr->wrapper.getDict(1).getSize() / 217798;
        ImGui::ProgressBar(en_progress, ImVec2(0.0f, 0.0f));
        
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Słownik francuski");
        static float fr_progress = 0.0f;
        fr_progress = (float)attr->wrapper.getDict(2).getSize() / 217798;
        ImGui::ProgressBar(fr_progress, ImVec2(0.0f, 0.0f));

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Słownik chiński");
        static float ch_progress = 0.0f;
        ch_progress = (float)attr->wrapper.getDict(3).getSize() / 217798;
        ImGui::ProgressBar(ch_progress, ImVec2(0.0f, 0.0f));

        if (gram_progress == 1.0f)
        {
            ImGui::CloseCurrentPopup();
            attr->dictsLoader.join();
        }
        ImGui::EndPopup();
    }

    //Wybór słownika

    static int selectedLang = 0;

    ImGui::Begin("Konfiguracja tłumaczenia", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    const char* langs[] = { "Angielski", "Francuski", "Chiński" };
    ImGui::Text("Język docelowy tłumaczenia");
    ImGui::Combo("##lang", &selectedLang, langs, 3);
    ImGui::Dummy(ImVec2(0.0f, 15.0f));

    //Zmiana ścieżek

    if (ImGui::Button("Zmień ścieżki programu", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        ImGui::OpenPopup("Zmień ścieżki programu");
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Zmień ścieżki programu", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Ścieżka do folderu zawierającego słowniki");
        static std::string dictPath;
        ImGui::InputText("##dictpath", &dictPath);

        ImGui::Text("Ścieżka do folderu wyjściowego");
        static std::string outPath;
        ImGui::InputText("##outpath", &outPath);

        ImGui::Dummy(ImVec2(0.0f, 15.0f));
        static std::string message;
        attr->wrapper.updatePathsFile(dictPath, outPath);
        bool valid = attr->wrapper.configurate(dictPath, outPath, message);
        if (ImGui::Button("Zapisz", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        {
            if (valid)
                ImGui::CloseCurrentPopup();
            else
                ImGui::OpenPopup("Błąd");
        }

        if (ImGui::BeginPopupModal("Błąd", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text(message.c_str());
            if (ImGui::Button("Ok", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }

        ImGui::EndPopup();
    }

    ImGui::End();

    //Tłumaczenie tekstu

    ImGui::Begin("Tłumaczenie tekstu", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    static std::string src, dest;

    ImGui::Text("Tekst do przetłumaczenia");
    ImGui::InputTextMultiline("##src", &src);

    ImGui::Dummy(ImVec2(0.0f, 25.f));
    if (ImGui::Button("Tłumacz", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
    {
        attr->wrapper.translate(src, dest, attr->wrapper.getDict(0), attr->wrapper.getDict(selectedLang + 1));
    }
    ImGui::Dummy(ImVec2(0.0f, 25.f));
        
    ImGui::Text("Tekst po przetłumaczeniu");
    ImGui::InputTextMultiline("##dest", &dest);

    ImGui::End();
    
    //Konfiguracja syntezy
    
    static int wordsPerMin = 150;

    ImGui::Begin("Konfiguracja syntezy", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Ilość słów na minutę");
    ImGui::SliderInt("##wordspermin", &wordsPerMin, 50, 500);
    ImGui::Dummy(ImVec2(0.0f, 15.0f));

    if (ImGui::Button("Syntezuj", ImVec2(ImGui::GetContentRegionAvail().x / 2, 0)))
        attr->wrapper.synthesizeIn(dest, wordsPerMin, selectedLang);
    ImGui::SameLine();

    if (ImGui::Button("Zapisz do pliku", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        ImGui::OpenPopup("Synteza do pliku");
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    
    if (ImGui::BeginPopupModal("Synteza do pliku", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Nazwa pliku dźwiękowego");
        static char filename[64];
        ImGui::InputText("##filename", filename, 64);
        ImGui::Dummy(ImVec2(0.0f, 15.0f));

        if (ImGui::Button("Zapisz", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        {
            ImGui::CloseCurrentPopup();
            attr->wrapper.synthesizeOut(dest, wordsPerMin, selectedLang, filename);
        }
        ImGui::EndPopup();
    }

    ImGui::End();
    
    //Konfiguracja interfejsu
    
    ImGui::Begin("Konfiguracja interfejsu", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Kolor tła programu");
    ImGui::ColorEdit3("##background", (float*)&attr->backgroundColor);
    ImGui::Dummy(ImVec2(0.0f, 15.0f));

    ImGui::Text("Styl okien programu");
    if (ImGui::Button("Tryb ciemny", ImVec2(ImGui::GetContentRegionAvail().x / 3, 0)))
        ImGui::StyleColorsDark();
    ImGui::SameLine();
    if (ImGui::Button("Tryb klasyczny", ImVec2(ImGui::GetContentRegionAvail().x / 2, 0)))
        ImGui::StyleColorsClassic();
    ImGui::SameLine();
    if (ImGui::Button("Tryb jasny", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        ImGui::StyleColorsLight();

    ImGui::End();
    
}
