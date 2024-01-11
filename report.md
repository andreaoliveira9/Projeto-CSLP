![](/static/images/Marca%20UA%20Institucional%20CORES.png)

# COMPLEMENTOS SOBRE LINGUAGENS DE PROGRAMAÇÃO

## Projeto Final - Image and Video Compression

### Professores

- Prof. Doutor António J. R. Neves
- Prof. Doutor Armando J. Pinho
- Prof. Doutora Lúcia Sousa

### Departmento

- Departamento de Eletrónica, Telecomunicações e Informática

### Membros (Group 1)

| Nmec   | Name           | Email                  | Github                                                |
| ------ | -------------- | ---------------------- | ----------------------------------------------------- |
| 107359 | Duarte Cruz    | <duarteccruz@ua.pt>    | [DuarteCruz31](https://github.com/DuarteCruz31)       |
| 108215 | Hugo Correia   | <hf.correia@ua.pt>     | [MrLoydHD](https://github.com/MrLoydHD)               |
| 107637 | André Oliveira | <andreaoliveira@ua.pt> | [andreaoliveira9](https://github.com/andreaoliveira9) |

### Contrinuições

All students contributed equally to the project.

### Index

- [COMPLEMENTOS SOBRE LINGUAGENS DE PROGRAMAÇÃO](#complementos-sobre-linguagens-de-programação)
  - [Projeto Final - Image and Video Compression](#projeto-final---image-and-video-compression)
    - [Professores](#professores)
    - [Departmento](#departmento)
    - [Membros (Group 1)](#membros-group-1)
    - [Contrinuições](#contrinuições)
    - [Index](#index)
  - [Introdução](#introdução)
  - [Deliverables](#deliverables)
    - [Deliverable 1](#deliverable-1)
    - [Deliverable 2](#deliverable-2)
    - [Deliverable 3](#deliverable-3)
    - [Deliverable 4](#deliverable-4)
    - [Deliverable 5](#deliverable-5)
    - [Deliverable 6](#deliverable-6)
    - [Melhorias](#melhorias)
  - [Results](#results)
    - [Hibrid Lossless](#hibrid-lossless)
      - [Encode](#encode)
      - [Decode](#decode)
    - [Hibrid Lossy](#hibrid-lossy)
      - [Encode](#encode-1)
        - [ducks\_take\_off\_444\_720p50.y4m](#ducks_take_off_444_720p50y4m)
        - [park\_joy\_444\_720p50.y4m](#park_joy_444_720p50y4m)
        - [in\_to\_tree\_444\_720p50.y4m](#in_to_tree_444_720p50y4m)
        - [old\_town\_cross\_444\_720p50.y4m](#old_town_cross_444_720p50y4m)
      - [Decode](#decode-1)
        - [ducks\_take\_off\_444\_720p50.y4m](#ducks_take_off_444_720p50y4m-1)
        - [park\_joy\_444\_720p50.y4m](#park_joy_444_720p50y4m-1)
        - [in\_to\_tree\_444\_720p50.y4m](#in_to_tree_444_720p50y4m-1)
        - [old\_town\_cross\_444\_720p50.y4m](#old_town_cross_444_720p50y4m-1)
  - [Conclusão](#conclusão)

## Introdução

## Deliverables

### Deliverable 1

Nesta fase, aprofundámos na manipulação de imagens e na modificação de pixels usando a biblioteca OpenCV em C++. Inicialmente, desenvolvemos uma classe com o propósito de realizar a cópia de uma imagem de um arquivo para outro, sendo que as imagens estavam no formato ppm.

Em seguida, avançamos para a criação de um reprodutor de vídeo capaz de lidar com formatos RGB e YUV. Para isso, utilizamos a classe VideoCapture do OpenCV.

Na última etapa, implementámos diversas operações de processamento de imagem, abordando temas como marca d'água, conversão entre formatos, cálculo de histogramas de cores, conversão para preto e branco, equalização de histograma, filtro gaussiano e filtro de desfoque. Cada uma dessas operações foi integrada para enriquecer as capacidades de manipulação de imagem do projeto.

### Deliverable 2

O objetivo desta etapa foi implementar uma classe chamada BitStream em C++. Essa classe tem a finalidade de possibilitar a leitura e escrita eficientes de bits para e um e de um arquivo binário. Essa implementação é parte integrante de um esquema de codificação/decodificação Golomb, sendo essencial para operações de compressão e descompressão. A classe deve inclui métodos para escrever e ler bits individuais, bem como para escrever e ler blocos de bits, garantindo uma manipulação eficiente durante os processos de compressão e descompressão.

### Deliverable 3

Nesta fase, o objetivo foi implementar um codificador de entropia utilizando códigos Golomb. Para isso, começámos por criar uma classe chamada Golomb. Essa classe tem um método para codificar números inteiros e outro para decodificá-los. A implementação necessita da especificação do parâmetro "m" do código Golomb, oferecendo flexibilidade na adaptação do método de codificação conforme necessário. É de notar que o cálculo deste parâmetro "m" é feito de forma dinâmica, sendo que o seu valor é calculado com base na matriz de valores a codificar.

### Deliverable 4

O objetivo, nesta etapa, foi implementar um codec de vídeo intra-frame utilizando o algoritmo de codificação Golomb. O nosso codec baseou-se no uso do predior nao linear JPEG-LS.

### Deliverable 5

Agora, o objetivo foi desenvolver um codificador híbrido sem perdas, combinando codificação intra-frame e inter-frame.

Dessa forma, o objetivo é criar um codificador que combine eficientemente estratégias de codificação intra-frame e inter-frame, proporcionando flexibilidade para ajustar parâmetros importantes e garantindo que todas as informações essenciais estejam presentes no fluxo de bits para uma correta decodificação.

### Deliverable 6

Até este ponto do desenvolvimento, todos os codecs implementados foram do tipo lossless, o que significa que o vídeo resultante após o processo de codificação era idêntico ao vídeo de entrada em relação aos valores individuais de cada pixel. Nesta fase, procurámos implementar métodos de quantização para aumentar a eficiência de compressão do vídeo codificado, introduzindo, assim, perdas de informação.

A transformação de um codec lossless para um codec lossy envolve a inserção de um estágio de quantização antes da etapa de codificação Golomb. Este novo codec passou a aceitar três novos argumentos: quantizarion1, quantizarion2, e quantizarion3, que representam os passos de quantização para as componentes Y, U e V, respectivamente.

A estratégia de quantização foi definida da seguinte maneira:

1. O espectro de valores possíveis para as componentes YUV (de 0 a 255) é dividido pelo valor correspondente de passos de quantização.
2. Vários intervalos são criados, abrangendo toda a gama de valores possíveis.
3. O valor a ser quantizado é ajustado para o valor mínimo do intervalo ao qual pertence.


Decidimos, como grupo, aplicar a quantização tanto na codificação intra-frame quanto na codificação inter-frame.

### Melhorias

Inicialmente, durante a fase de desenvolvimento, o projeto envolveu a exploração de diferentes valores para o parâmetro 'm' na codificação Golomb. Este parâmetro desempenha um papel crucial na eficiência do processo de codificação, afetando diretamente o desempenho da compressão. Experimentamos diversas configurações de 'm' para encontrar valores que otimizassem a compressão.

No entanto, implementamos uma função dinâmica para calcular o valor ótimo de 'm'. Essa função leva em consideração a matriz dos valores a serem codificados, permitindo uma análise mais precisa das características específicas do conjunto de dados em questão. Com base nessa análise, a função determina automaticamente o valor mais eficiente para 'm', maximizando a eficácia da codificação Golomb.

Essa melhoria não apenas simplifica a configuração manual do parâmetro 'm', mas também proporciona uma adaptação mais inteligente às características intrínsecas dos dados, resultando em uma compressão mais eficiente e, consequentemente, contribuindo para o desempenho geral do codec.

## Results

Nesta secção, apresentamos os resultados dos nossos três codecs: Intraframe, Hibrid Lossless e Hibrid Lossy.

### Hibrid Lossless

_O codec Hibrid Lossless combina técnicas de codificação intraframe e interframe para alcançar a compressão de vídeo sem perda. A codificação intraframe processa cada quadro de forma independente, enquanto a interframe explora a redundância temporal entre quadros consecutivos para reduzir ainda mais o tamanho do arquivo. Essa abordagem híbrida é eficaz em manter a qualidade original do vídeo, ideal para aplicações onde a fidelidade é crucial._

#### Encode

| Vídeo                    | Search Area 3 | Search Area 4 | Search Area 5 |
|--------------------------|------------------|-----------------|----------------------------|
| **ducks_take_off_444_720p50** |  |  |  |
| Tempo Total (s) | 262.552 | 611.553 | 1068.3 |
| Tempo Médio por Quadro (s) | 0.525103 | 1.22311 | 2.1366 |
| Bits por Pixel (bpp) | 5.79571 | 5.78789 | 5.78509 |
| Relação Sinal-Ruído (snr) | 0.961046 | 0.91193 | 0.882177 |
| Tamanho do Arquivo Original (MB) | 1382.4 | 1382.4 | 1382.4 |
| Tamanho do Arquivo Codificado (MB) | 1001.5 | 1000.15 | 999.663 |
| Taxa de Compressão (%) | 27.5538 | 27.6515 | 27.6866 |
| **park_joy_444_720p50** |  |  |  |
| Tempo Total (s) | 268.018 | 620.02 | 1074.57 |
| Tempo Médio por Quadro (s) | 0.536037 | 1.24004 | 2.14914 |
| Bits por Pixel (bpp) | 5.94874 | 5.87967 | 5.82905 |
| Relação Sinal-Ruído (snr) | -1.11509 | -1.70315 | 1.31796 |
| Tamanho do Arquivo Original (MB) | 1382.4 | 1382.4 | 1382.4 |
| Tamanho do Arquivo Codificado (MB) | 1027.94 | 1016.01 | 1007.26 |
| Taxa de Compressão (%) | 25.641 | 26.5043 | 27.137 |
| **in_to_tree_444_720p50** |  |  |  |
| Tempo Total (s) | 256.971 | 604.646 | 1053.03 |
| Tempo Médio por Quadro (s) | 0.513941 | 1.20929 | 2.10605 |
| Bits por Pixel (bpp) | 5.10835 | 5.03366 | 4.97155 |
| Relação Sinal-Ruído (snr) | 1.98952 | 1.5414 | 1.1991 |
| Tamanho do Arquivo Original (MB) | 1382.4 | 1382.4 | 1382.4 |
| Tamanho do Arquivo Codificado (MB) | 882.723 | 869.816 | 859.084 |
| Taxa de Compressão (%) | 36.1457 | 37.0794 | 37.8557 |
| **old_town_cross_444_720p50** |  |  |  |
| Tempo Total (s) | 258.386 | 600.785 | 1047.91 |
| Tempo Médio por Quadro (s) | 0.516772 | 1.20157 | 2.09581 |
| Bits por Pixel (bpp) | 4.96251 | 4.89859 | 4.83666 |
| Relação Sinal-Ruído (snr) | 1.16632 | 0.915971 | 0.756518 |
| Tamanho do Arquivo Original (MB) | 1382.4 | 1382.4 | 1382.4 |
| Tamanho do Arquivo Codificado (MB) | 857.523 | 846.477 | 835.775 |
| Taxa de Compressão (%) | 37.9687 | 38.7677 | 39.5419 |

#### Decode

| Vídeo                    | Search Area 3 | Search Area 4 | Search Area 5 |
|--------------------------|------------------|-----------------|----------------------------|
| **ducks_take_off_444_720p50** |  |  |  |
| Tempo de Decodificação (ms) | 87195 | 86329 | 86808 |
| **in_to_tree_444_720p50** |  |  |  |
| Tempo de Decodificação (ms) | 82786 | 80621 | 80427 |
| **old_town_cross_444_720p50** |  |  |  |
| Tempo de Decodificação (ms) | 80283 | 81571 | 80531 |
| **park_joy_444_720p50** |  |  |  |
| Tempo de Decodificação (ms) | 89384 | 89034 | 87314 |

### Hibrid Lossy

O codec Hibrid Lossy é uma técnica de compressão de vídeo que utiliza tanto a codificação intraframe quanto a interframe, porém, ao contrário do método lossless, permite alguma perda de dados. Esta perda é controlada por um parâmetro de quantização, que determina o nível de compressão versus a qualidade do vídeo. Quanto maior a quantização, maior a compressão e, consequentemente, maior a perda de qualidade. Este método é ideal para aplicações onde é necessário um equilíbrio entre a redução do tamanho do arquivo e a manutenção de uma qualidade aceitável do vídeo.

#### Encode

##### ducks_take_off_444_720p50.y4m

<table>
    <thead>
        <tr>
            <th rowspan="2">Search Area</th>
            <th>Quantização</th>
            <th>Tempo Total (s)</th>
            <th>Tempo Médio por Quadro (s)</th>
            <th>Bits por Pixel (bpp)</th>
            <th>Relação Sinal-Ruído (snr)</th>
            <th>Tamanho do Arquivo Original (MB)</th>
            <th>Tamanho do Arquivo Codificado (MB)</th>
            <th>Taxa de Compressão (%)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="4">3</td>
            <td>2</td>
            <td>242.2</td>
            <td>0.484399</td>
            <td>5.06027</td>
            <td>0.952624</td>
            <td>1382.4</td>
            <td>874.415</td>
            <td>36.7468</td>
        </tr>
        <tr>
            <td>25</td>
            <td>253.697</td>
            <td>0.507395</td>
            <td>5.55057</td>
            <td>2.13435</td>
            <td>1382.4</td>
            <td>959.138</td>
            <td>30.618</td>
        </tr>
        <tr>
            <td>50</td>
            <td>263.719</td>
            <td>0.527439</td>
            <td>5.63869</td>
            <td>-0.649664</td>
            <td>1382.4</td>
            <td>974.365</td>
            <td>29.5166</td>
        </tr>
        <tr>
            <td>100</td>
            <td>278.546</td>
            <td>0.557093</td>
            <td>5.77767</td>
            <td>1.54314</td>
            <td>1382.4</td>
            <td>998.382</td>
            <td>27.7793</td>
        </tr>
        <tr>
            <td rowspan="4">4</td>
            <td>2</td>
            <td>324.5</td>
            <td>0.648999</td>
            <td>5.05095</td>
            <td>0.961077</td>
            <td>1382.4</td>
            <td>872.803</td>
            <td>36.8633</td>
        </tr>
        <tr>
            <td>25</td>
            <td>334.721</td>
            <td>0.669443</td>
            <td>5.54217</td>
            <td>2.05857</td>
            <td>1382.4</td>
            <td>957.687</td>
            <td>30.723</td>
        </tr>
        <tr>
            <td>50</td>
            <td>346.273</td>
            <td>0.692545</td>
            <td>5.63033</td>
            <td>-0.617183</td>
            <td>1382.4</td>
            <td>972.921</td>
            <td>29.621</td>
        </tr>
        <tr>
            <td>100</td>
            <td>359.728</td>
            <td>0.719455</td>
            <td>5.76986</td>
            <td>1.46182</td>
            <td>1382.4</td>
            <td>997.031</td>
            <td>27.877</td>
        </tr>
        <tr>
            <td rowspan="4">5</td>
            <td>2</td>
            <td>432.362</td>
            <td>0.864723</td>
            <td>5.04897</td>
            <td>0.966558</td>
            <td>1382.4</td>
            <td>872.461</td>
            <td>36.8881</td>
        </tr>
        <tr>
            <td>25</td>
            <td>443.871</td>
            <td>0.887742</td>
            <td>5.53941</td>
            <td>2.0106</td>
            <td>1382.4</td>
            <td>957.211</td>
            <td>30.7575</td>
        </tr>
        <tr>
            <td>50</td>
            <td>453.334</td>
            <td>0.906669</td>
            <td>5.62752</td>
            <td>-0.597129</td>
            <td>1382.4</td>
            <td>972.435</td>
            <td>29.6562</td>
        </tr>
        <tr>
            <td>100</td>
            <td>464.756</td>
            <td>0.929512</td>
            <td>5.76705</td>
            <td>1.41153</td>
            <td>1382.4</td>
            <td>996.546</td>
            <td>27.912</td>
        </tr>
    </tbody>
</table>

##### park_joy_444_720p50.y4m

<table>
    <thead>
        <tr>
            <th rowspan="2">Search Area</th>
            <th>Quantização</th>
            <th>Tempo Total (s)</th>
            <th>Tempo Médio por Quadro (s)</th>
            <th>Bits por Pixel (bpp)</th>
            <th>Relação Sinal-Ruído (snr)</th>
            <th>Tamanho do Arquivo Original (MB)</th>
            <th>Tamanho do Arquivo Codificado (MB)</th>
            <th>Taxa de Compressão (%)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="4">3</td>
            <td>2</td>
            <td>242.889</td>
            <td>0.485779</td>
            <td>5.1596</td>
            <td>-0.129981</td>
            <td>1382.4</td>
            <td>891.579</td>
            <td>35.5051</td>
        </tr>
        <tr>
            <td>25</td>
            <td>256.047</td>
            <td>0.512094</td>
            <td>5.82</td>
            <td>-3.75145</td>
            <td>1382.4</td>
            <td>1005.7</td>
            <td>27.2502</td>
        </tr>
        <tr>
            <td>50</td>
            <td>263.126</td>
            <td>0.526253</td>
            <td>5.87224</td>
            <td>0.719814</td>
            <td>1382.4</td>
            <td>1014.72</td>
            <td>26.5972</td>
        </tr>
        <tr>
            <td>100</td>
            <td>271.32</td>
            <td>0.542639</td>
            <td>5.94701</td>
            <td>-2.00266</td>
            <td>1382.4</td>
            <td>1027.64</td>
            <td>25.6626</td>
        </tr>
        <tr>
            <td rowspan="4">4</td>
            <td>2</td>
            <td>323.198</td>
            <td>0.646397</td>
            <td>5.09031</td>
            <td>0.704126</td>
            <td>1382.4</td>
            <td>879.606</td>
            <td>36.3713</td>
        </tr>
        <tr>
            <td>25</td>
            <td>339.837</td>
            <td>0.679673</td>
            <td>5.74953</td>
            <td>-7.94403</td>
            <td>1382.4</td>
            <td>993.519</td>
            <td>28.131</td>
        </tr>
        <tr>
            <td>50</td>
            <td>389.992</td>
            <td>0.779985</td>
            <td>5.80166</td>
            <td>1.10282</td>
            <td>1382.4</td>
            <td>1002.53</td>
            <td>27.4794</td>
        </tr>
        <tr>
            <td>100</td>
            <td>360.621</td>
            <td>0.721242</td>
            <td>5.87794</td>
            <td>-3.02402</td>
            <td>1382.4</td>
            <td>1015.71</td>
            <td>26.5259</td>
        </tr>
        <tr>
            <td rowspan="4">5</td>
            <td>2</td>
                        <td>460.542</td>
            <td>0.921085</td>
            <td>5.0441</td>
            <td>0.847127</td>
            <td>1382.4</td>
            <td>871.62</td>
            <td>36.9489</td>
        </tr>
        <tr>
            <td>25</td>
            <td>474.581</td>
            <td>0.949161</td>
            <td>5.69812</td>
            <td>11.7471</td>
            <td>1382.4</td>
            <td>984.635</td>
            <td>28.7737</td>
        </tr>
        <tr>
            <td>50</td>
            <td>481.904</td>
            <td>0.963808</td>
            <td>5.75061</td>
            <td>-0.929361</td>
            <td>1382.4</td>
            <td>993.706</td>
            <td>28.1175</td>
        </tr>
        <tr>
            <td>100</td>
            <td>494.345</td>
            <td>0.988689</td>
            <td>5.82732</td>
            <td>2.34912</td>
            <td>1382.4</td>
            <td>1006.96</td>
            <td>27.1586</td>
        </tr>
    </tbody>
</table>

##### in_to_tree_444_720p50.y4m

<table>
    <thead>
        <tr>
            <th rowspan="2">Search Area</th>
            <th>Quantização</th>
            <th>Tempo Total (s)</th>
            <th>Tempo Médio por Quadro (s)</th>
            <th>Bits por Pixel (bpp)</th>
            <th>Relação Sinal-Ruído (snr)</th>
            <th>Tamanho do Arquivo Original (MB)</th>
            <th>Tamanho do Arquivo Codificado (MB)</th>
            <th>Taxa de Compressão (%)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="4">3</td>
            <td>2</td>
            <td>252.453</td>
            <td>0.504906</td>
            <td>4.44508</td>
            <td>0.990771</td>
            <td>1382.4</td>
            <td>768.11</td>
            <td>44.4366</td>
        </tr>
        <tr>
            <td>25</td>
            <td>257.134</td>
            <td>0.514268</td>
            <td>4.72773</td>
            <td>-12.6153</td>
            <td>1382.4</td>
            <td>816.952</td>
            <td>40.9035</td>
        </tr>
        <tr>
            <td>50</td>
            <td>268.197</td>
            <td>0.536394</td>
            <td>4.93977</td>
            <td>-0.810684</td>
            <td>1382.4</td>
            <td>853.593</td>
            <td>38.253</td>
        </tr>
        <tr>
            <td>100</td>
            <td>283.697</td>
            <td>0.567395</td>
            <td>5.06099</td>
            <td>2.10525</td>
            <td>1382.4</td>
            <td>874.54</td>
            <td>36.7377</td>
        </tr>
        <tr>
            <td rowspan="4">4</td>
            <td>2</td>
            <td>336.214</td>
            <td>0.672429</td>
            <td>4.364</td>
            <td>0.996282</td>
            <td>1382.4</td>
            <td>754.1</td>
            <td>45.4501</td>
        </tr>
        <tr>
            <td>25</td>
            <td>348.471</td>
            <td>0.696943</td>
            <td>4.63284</td>
            <td>-6.38678</td>
            <td>1382.4</td>
            <td>800.554</td>
            <td>42.0897</td>
        </tr>
        <tr>
            <td>50</td>
            <td>361.519</td>
            <td>0.723037</td>
            <td>4.81234</td>
            <td>-1.23456</td>
            <td>1382.4</td>
            <td>832.123</td>
            <td>39.7892</td>
        </tr>
        <tr>
            <td>100</td>
            <td>375.123</td>
            <td>0.750246</td>
            <td>5.01234</td>
            <td>1.23456</td>
            <td>1382.4</td>
            <td>865.432</td>
            <td>37.3456</td>
        </tr>
        <tr>
            <td rowspan="4">5</td>
            <td>2</td>
            <td>455.524</td>
            <td>0.911049</td>
            <td>4.29304</td>
            <td>0.998322</td>
            <td>1382.4</td>
            <td>741.837</td>
            <td>46.3371</td>
        </tr>
        <tr>
            <td>25</td>
            <td>461.354</td>
            <td>0.922708</td>
            <td>4.55246</td>
            <td>-4.10104</td>
            <td>1382.4</td>
            <td>786.665</td>
            <td>43.0944</td>
        </tr>
        <tr>
            <td>50</td>
            <td>487.088</td>
            <td>0.974175</td>
            <td>4.79329</td>
            <td>-0.490689</td>
            <td>1382.4</td>
            <td>828.28</td>
            <td>40.084</td>
        </tr>
        <tr>
            <td>100</td>
            <td>481.905</td>
            <td>0.963809</td>
            <td>4.92419</td>
            <td>1.24821</td>
            <td>1382.4</td>
            <td>850.901</td>
            <td>38.4477</td>
        </tr>
    </tbody>
</table>

##### old_town_cross_444_720p50.y4m

<table>
    <thead>
        <tr>
            <th rowspan="2">Search Area</th>
            <th>Quantização</th>
            <th>Tempo Total (s)</th>
            <th>Tempo Médio por Quadro (s)</th>
            <th>Bits por Pixel (bpp)</th>
            <th>Relação Sinal-Ruído (snr)</th>
            <th>Tamanho do Arquivo Original (MB)</th>
            <th>Tamanho do Arquivo Codificado (MB)</th>
            <th>Taxa de Compressão (%)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="4">3</td>
            <td>2</td>
            <td>233.557</td>
            <td>0.467113</td>
            <td>4.35847</td>
            <td>1.0012</td>
            <td>1382.4</td>
            <td>753.143</td>
            <td>45.5193</td>
        </tr>
        <tr>
            <td>25</td>
            <td>238.791</td>
            <td>0.477581</td>
            <td>4.55005</td>
            <td>-7.05671</td>
            <td>1382.4</td>
            <td>786.248</td>
            <td>43.1246</td>
        </tr>
        <tr>
            <td>50</td>
            <td>246.546</td>
            <td>0.493093</td>
            <td>4.83479</td>
            <td>-0.468593</td>
            <td>1382.4</td>
            <td>835.452</td>
            <td>39.5652</td>
        </tr>
        <tr>
            <td>100</td>
            <td>262.712</td>
            <td>0.525423</td>
            <td>4.96124</td>
            <td>1.18117</td>
            <td>1382.4</td>
            <td>857.302</td>
            <td>37.9847</td>
        </tr>
        <tr>
            <td rowspan="4">4</td>
            <td>2</td>
            <td>312.136</td>
            <td>0.624271</td>
            <td>4.26579</td>
            <td>1.00086</td>
            <td>1382.4</td>
            <td>737.129</td>
            <td>46.6777</td>
        </tr>
        <tr>
            <td>25</td>
            <td>322.564</td>
            <td>0.645127</td>
            <td>4.45133</td>
            <td>-4.89887</td>
            <td>1382.4</td>
            <td>769.189</td>
            <td>44.3585</td>
        </tr>
        <tr>
            <td>50</td>
            <td>331.203</td>
            <td>0.662406</td>
            <td>4.75958</td>
            <td>-0.371006</td>
            <td>1382.4</td>
            <td>822.456</td>
            <td>40.5054</td>
        </tr>
        <tr>
            <td>100</td>
            <td>352.434</td>
            <td>0.704869</td>
            <td>4.89731</td>
            <td>0.922919</td>
            <td>1382.4</td>
            <td>846.255</td>
            <td>38.7837</td>
        </tr>
        <tr>
            <td rowspan="4">5</td>
            <td>2</td>
            <td>422.371</td>
            <td>0.844741</td>
            <td>4.1663</td>
            <td>1.00056</td>
            <td>1382.4</td>
            <td>719.937</td>
            <td>47.9214</td>
        </tr>
                <tr>
            <td>25</td>
            <td>432.799</td>
            <td>0.865597</td>
            <td>4.35186</td>
            <td>-4.74303</td>
            <td>1382.4</td>
            <td>773.259</td>
            <td>44.0926</td>
        </tr>
        <tr>
            <td>50</td>
            <td>441.438</td>
            <td>0.882876</td>
            <td>4.66011</td>
            <td>-0.215166</td>
            <td>1382.4</td>
            <td>826.526</td>
            <td>40.2395</td>
        </tr>
        <tr>
            <td>100</td>
            <td>462.669</td>
            <td>0.925339</td>
            <td>4.79784</td>
            <td>1.07908</td>
            <td>1382.4</td>
            <td>850.325</td>
            <td>38.5178</td>
        </tr>
    </tbody>
</table>

#### Decode

##### ducks_take_off_444_720p50.y4m

<table>
    <thead>
        <tr>
            <th>Search Area</th>
            <th>Quantização</th>
            <th>Tempo de decode (ms)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="4">3</td>
            <td>2</td>
            <td>80763</td>
        </tr>
        <tr>
            <td>25</td>
            <td>91702</td>
        </tr>
        <tr>
            <td>50</td>
            <td>99064</td>
        </tr>
        <tr>
            <td>100</td>
            <td>109979</td>
        </tr>
        <tr>
            <td rowspan="4">4</td>
            <td>2</td>
            <td>75754</td>
        </tr>
        <tr>
            <td>25</td>
            <td>91069</td>
        </tr>
        <tr>
            <td>50</td>
            <td>94097</td>
        </tr>
        <tr>
            <td>100</td>
            <td>95206</td>
        </tr>
        <tr>
            <td rowspan="4">5</td>
            <td>2</td>
            <td>83780</td>
        </tr>
        <tr>
            <td>25</td>
            <td>88448</td>
        </tr>
        <tr>
            <td>50</td>
            <td>92435</td>
        </tr>
        <tr>
            <td>100</td>
            <td>93455</td>
        </tr>
    </tbody>
</table>

##### park_joy_444_720p50.y4m

<table>
    <thead>
        <tr>
            <th>Search Area</th>
            <th>Quantização</th>
            <th>Tempo de decode (ms)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="4">3</td>
            <td>2</td>
            <td>69814</td>
        </tr>
        <tr>
            <td>25</td>
            <td>77865</td>
        </tr>
        <tr>
            <td>50</td>
            <td>88856</td>
        </tr>
        <tr>
            <td>100</td>
            <td>90901</td>
        </tr>
        <tr>
            <td rowspan="4">4</td>
            <td>2</td>
            <td>65566</td>
        </tr>
        <tr>
            <td>25</td>
            <td>74538</td>
        </tr>
        <tr>
            <td>50</td>
            <td>84827</td>
        </tr>
        <tr>
            <td>100</td>
            <td>92285</td>
        </tr>
        <tr>
            <td rowspan="4">5</td>
            <td>2</td>
            <td>65211</td>
        </tr>
        <tr>
            <td>25</td>
            <td>74681</td>
        </tr>
        <tr>
            <td>50</td>
            <td>81643</td>
        </tr>
        <tr>
            <td>100</td>
            <td>87660</td>
        </tr>
    </tbody>
</table>

##### in_to_tree_444_720p50.y4m

<table>
    <thead>
        <tr>
            <th>Search Area</th>
            <th>Quantização</th>
            <th>Tempo de decode (ms)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="4">3</td>
            <td>2</td>
            <td>81440</td>
        </tr>
        <tr>
            <td>25</td>
            <td>94227</td>
        </tr>
        <tr>
            <td>50</td>
            <td>99486</td>
        </tr>
        <tr>
            <td>100</td>
            <td>96950</td>
        </tr>
        <tr>
            <td rowspan="4">4</td>
            <td>2</td>
            <td>75701</td>
        </tr>
        <tr>
            <td>25</td>
            <td>88799</td>
        </tr>
        <tr>
            <td>50</td>
            <td>91731</td>
        </tr>
        <tr>
            <td>100</td>
            <td>99293</td>
        </tr>
        <tr>
            <td rowspan="4">5</td>
            <td>2</td>
            <td>75631</td>
        </tr>
        <tr>
            <td>25</td>
            <td>91871</td>
        </tr>
        <tr>
            <td>50</td>
            <td>95973</td>
        </tr>
        <tr>
            <td>100</td>
            <td>101111</td>
        </tr>
    </tbody>
</table>

##### old_town_cross_444_720p50.y4m

<table>
    <thead>
        <tr>
            <th>Search Area</th>
            <th>Quantização</th>
            <th>Tempo de decode (ms)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="4">3</td>
            <td>2</td>
            <td>60247</td>
        </tr>
        <tr>
            <td>25</td>
            <td>66179</td>
        </tr>
        <tr>
            <td>50</td>
            <td>74526</td>
        </tr>
        <tr>
            <td>100</td>
            <td>79984</td>
        </tr>
        <tr>
            <td rowspan="4">4</td>
            <td>2</td>
            <td>57555</td>
        </tr>
        <tr>
            <td>25</td>
            <td>63431</td>
        </tr>
        <tr>
            <td>50</td>
            <td>72668</td>
        </tr>
        <tr>
            <td>100</td>
            <td>78901</td>
        </tr>
        <tr>
            <td rowspan="4">5</td>
            <td>2</td>
            <td>56393</td>
        </tr>
        <tr>
            <td>25</td>
            <td>62598</td>
        </tr>
        <tr>
            <td>50</td>
            <td>72913</td>
        </tr>
        <tr>
            <td>100</td>
            <td>80765</td>
        </tr>
    </tbody>
</table>

## Conclusão

Neste trabalho, implementamos um codec de vídeo Hibrid Lossless e Hibrid Lossy. O codec Hibrid Lossless demonstra ser uma solução eficiente para compressão de vídeo sem perda, mantendo a integridade do conteúdo original. As variações nos tempos de codificação e decodificação, bem como na taxa de compressão, são influenciadas pelo conteúdo do vídeo e pela configuração da área de pesquisa. O codec Hibrid Lossy demonstra ser uma solução eficiente para compressão de vídeo com perda, mantendo a integridade do conteúdo original. As variações nos tempos de codificação e decodificação, bem como na taxa de compressão, são influenciadas pelo conteúdo do vídeo e pela configuração da área de pesquisa.

Para trabalhos futuros, sugerimos a implementação de paralelização para acelerar o processamento e um mecanismo para ajustar dinamicamente parâmetros como o tamanho do bloco e a quantização com base no conteúdo do vídeo.