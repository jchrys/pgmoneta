\newpage

# [रिटेंशन पॉलिसी]{lang=hi}

[रिटेंशन पॉलिसी यह निर्धारित करती है कि एक बैकअप को कितने समय तक रखा जाना चाहिए।]{lang=hi}

## [रिटेंशन कॉन्फ़िगरेशन]{lang=hi}

[कॉन्फ़िगरेशन मुख्य कॉन्फ़िगरेशन सेक्शन में की जाती है, या सर्वर के आधार पर भी की जा सकती है:]{lang=hi}

| [प्रॉपर्टी]{lang=hi} | [डिफ़ॉल्ट]{lang=hi} | [यूनिट]{lang=hi} | [आवश्यक]{lang=hi} | [विवरण]{lang=hi} |
| :------- | :------ | :--- | :------- | :---------- |
| retention | 7, - , - , - | Array | [नहीं]{lang=hi} | [बैकअप का रिटेंशन समय दिन, सप्ताह, महीने, वर्षों में]{lang=hi}|

[यह यह बताता है कि डिफ़ॉल्ट रूप से बैकअप्स को 7 दिनों तक रखा जाता है।]{lang=hi}

## [रिटेंशन को परिभाषित करना]{lang=hi}

[रिटेंशन पॉलिसी को परिभाषित करना बहुत महत्वपूर्ण है क्योंकि यह यह निर्धारित करता है कि आप बैकअप्स से सिस्टम को कैसे बहाल करेंगे।]{lang=hi}

[मुख्य बात यह है कि आपको अपनी पॉलिसी तय करनी है, उदाहरण के लिए:]{lang=hi}

```
7, 4, 12, 5
```

[इसका मतलब है कि बैकअप्स को 7 दिन तक रखा जाए, हर सोमवार को 4 हफ्तों के लिए एक बैकअप, प्रत्येक महीने के लिए एक बैकअप, और 5 वार्षिक बैकअप्स।]{lang=hi}

[यह एक कठिन प्रॉपर्टी है जिसे कॉन्फ़िगर करना, क्योंकि यह डेटाबेस क्लस्टर के आकार पर निर्भर करता है और इस प्रकार बैकअप्स का आकार कितना बड़ा होगा।]{lang=hi}

[यदि आप नवीनतम बैकअप और]{lang=hi} Write-Ahead Log (WAL) [से सिस्टम को पुनर्स्थापित करना चाहते हैं, तो डिफ़ॉल्ट]{lang=hi} [**pgmoneta**](pgmoneta) [पॉलिसी शायद पर्याप्त हो सकती है।]{lang=hi}

[ध्यान दें कि यदि किसी बैकअप में कोई वृद्धिशील]{lang=hi} (incremental) [बैकअप चाइल्ड है जो उस पर निर्भर करता है, तो उसे बनाए रखा जाएगा, भले ही वह रिटेंशन नीति]{lang=hi} (retention policy) [के अंतर्गत न आता हो। हम भविष्य के संस्करणों में वृद्धिशील बैकअप को हटाने का समर्थन करेंगे।]{lang=hi}

## [रिटेंशन चेक]{lang=hi}

[रिटेंशन चेक हर 5 मिनट में चलता है, और प्रत्येक रन में एक बैकअप को हटा देगा।]{lang=hi}

[आप इसे हर 30 मिनट में बदल सकते हैं:]{lang=hi}

```
retention_interval = 1800
```

[यह]{lang=hi} `[pgmoneta]` [कॉन्फ़िगरेशन के तहत किया जा सकता है।]{lang=hi}
