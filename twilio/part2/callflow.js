/*
このプログラムはsakura.ioとTwilioとのコラボハンズオンにおいて、Twilio Functionsと連携させるためのものです。
こちらで生成されたURLをsakura.ioのOutgoing Webhookで指定することにより、sakura.ioで取得されたセンサデータはJSONデータとして本プログラムで処理されます。

本プログラムの動作に必要なパッケージはありません。

パラメータは以下のように指定します。
PATH : /callflow
ACCESS CONTROL ： チェックなし
EVENT ： 指定なし
*/
exports.handler = function(context, event, callback) {
    // モジュールからのメッセージの場合のみ処理を行う(切断・接続メッセージなどは無視) Determining the message type
    const messageType = event.type;
    if (messageType !== "channels") {
        console.log("messageType is not channels");
        callback(null, 'ignored messageType');
    }

    // JSONデータに含まれるモジュールIDを変数に代入 Substitute the module ID included in the JSON data
    const moduleId = event.module || '';

    const twilioClient = context.getTwilioClient();
    twilioClient.studio.flows('FWから始まるStudioフローのSID').engagements.create({ 
        to: context.TO_NUMBER, 
        from: context.FROM_NUMBER, 
        parameters: JSON.stringify({
            moduleId: moduleId
        })
    })
    .then(function(engagement) { 
        console.log(engagement.sid); 
        callback(null, engagement.sid);        
    })
    .catch(error => {
        console.error(`problem with request: ${error.message}`);
        callback(error.message);
    });
};