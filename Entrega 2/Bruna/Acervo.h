#ifndef ACERVO_H
#define ACERVO_H

#include "Livro.h"
#include <vector>

using std::vector;

class Acervo {
    private:
        vector<Livro> acervo;

    public:
        Acervo();
        
        void setAcervo (const vector<Livro>& novoAcervo);

        vector<Livro> getAcervo() const;

};

#endif