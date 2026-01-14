[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AFS01

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/afs01/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AFS01は、高精度、高再現性、長期安定性を備え、完全校正済みのマイクロガス流量センサです。当社が独自に開発・製造したフローチップを採用し、熱伝導原理を用いてガス流量を測定します。センサ内部には、熱フローチップと高性能24ビットAD取得CMOSマイクロプロセッサが統合されています。本製品は、高い集積度とコスト効率といったメリットを誇ります。

LibDriver AFS01は、LibDriverがリリースしたフル機能のドライバです。このドライバは、ガス流量の読み取りなどの機能を提供し、MISRA標準に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver AFS01のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver AFS01用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver AFS01ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver AFS01プログラミング例が含まれています。

/ docディレクトリには、LibDriver AFS01オフラインドキュメントが含まれています。

/ datasheetディレクトリには、AFS01データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_afs01_basic.h"

uint8_t res;
uint32_t i;

/* basic init */
res = afs01_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* read data */
for (i = 0; i < 3; i++)
{
    float sccm;

    /* delay 1000ms */
    afs01_interface_delay_ms(1000);

    /* read data */
    res = afs01_basic_read(&sccm);
    if (res != 0)
    {
        afs01_interface_debug_print("afs01: read data failed.\n");

        return 1;
    }

    /* output */
    afs01_interface_debug_print("afs01: gas flow is %0.1fsccm.\n", sccm);
    
    ...
}

...
    
/* deinit */
(void)afs01_basic_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/afs01/index.html](https://www.libdriver.com/docs/afs01/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。