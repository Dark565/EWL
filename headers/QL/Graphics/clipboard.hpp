#include <string>
#include <QL/Graphics/pixmap.hpp>

namespace ql {
    namespace gui {

        /*Gets text from clipboard*/
        std::string getTextFromClipboard();

        /*Saves text to clipboard*/
        void saveTextInClipboard();

        /*Gets pixmap from clipboard*/
        Pixmap getPixmapFromClipboard();

        /*Saves pixmap to clipboard*/
        void savePixmapInClipobard(const Pixmap& pix);

    }
}