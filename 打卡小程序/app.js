// app.js
App({
  //小程序启动
  onLaunch(){
    console.log('小程序启动啦！')
    wx.cloud.init({
      env:"mini-cloud-7g4rvuxx032fc668"
      })
  }
})


