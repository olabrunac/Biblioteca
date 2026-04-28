#ifndef LOCALIZACAOPRATELEIRA_H
#define LOCALIZACAOPRATELEIRA_H

class LocalizacaoPrateleira {
    private:
        int andar;
        int corredor;
        int prateleira;
        int secao;

    public:
        LocalizacaoPrateleira();
        void imprimirLocalizacaoPrateleira();

        int getAndar();
        int getCorredor();
        int getPrateleira();
        int getSecao();

        void setAndar(int novoAndar);
        void setCorredor(int novoCorredor);
        void setPrateleira(int novaPrateleira);
        void setSecao(int novaSecao);
};

#endif