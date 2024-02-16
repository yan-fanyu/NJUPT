

// pages/user/user.js
Page({
  
  /**
   * 页面的初始数据
   */
  data: {
     user_id: "",
     user_name: "未登录",
     user_image: "",
     user_phone:"",
     user_email:""
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    this.setData({
      user_phone: options.user_phone,
      user_email:options.user_email
    })
  },

  goToUserInfo() {
    
    // 使用 wx.navigateTo 进行页面跳转，并传递参数
    wx.navigateTo({
      url: `/pages/per_info/per_info?user_id=${this.data.user_id}&user_image=${encodeURIComponent(this.data.user_image)}&user_name=${encodeURIComponent(this.data.user_name)}&user_phone=${encodeURIComponent(this.data.user_phone)}&user_email=${encodeURIComponent(this.data.user_email)}`
    });
  },

  logout() {
    // 清空用户信息并更新数据
    this.setData({
      user_id: '',
      user_image: '/images/default_user_image.png',
      user_name: '未登录'
    });
    // 进行其他登出操作，例如清除本地存储、退出登录状态等
    //  wx.clearStorageSync(); // 如果使用了本地存储用户数据
  },


  loginUser(){

    if(this.data.user_name === '未登录'){
      wx.getUserProfile({
        desc: '用于完善会员资料', // 说明获取用户信息的原因
        success: (res) => {
          console.log(res.userInfo);
          this.setData({
            
            user_name:res.userInfo.nickName,
            user_image:res.userInfo.avatarUrl
          });
          // 用户同意授权后，获取用户信息成功，可以将信息发送到云函数处理
          this.onLoginSuccess(res.userInfo);
        },
        fail: (err) => {
          // 用户拒绝授权，可以在这里处理
          console.log('用户拒绝授权', err);
        }
      });
    }
    
  },
  onLoginSuccess(userInfo) {
    let that = this
    // 调用云函数进行登录
    wx.cloud.callFunction({
      name: 'login',
      data: {
        action: 'getUserInfo',
        userInfo: userInfo
      },
      success: res => {
        console.log('云函数获取到的用户openid: ', res.result.openid);
        that.setData({
          user_id:res.result.openid
        })
        console.log("用户的id:"+that.data.user_id);
        // 可以在这里进行后续登录逻辑，比如存储用户信息等
      },
      fail: err => {
        console.error('云函数调用失败', err);
      }
    });
  },
  
  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady() {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow() {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide() {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload() {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh() {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom() {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage() {

  }
})