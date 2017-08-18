import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';
import { Observable } from 'rxjs/Observable';
import * as jsmpeg from 'jsmpeg';
import { Http } from '@angular/http';
import 'rxjs/add/operator/map';



@Component({
  selector: 'page-films',
  templateUrl: 'home.html',
})
export class HomePage {
  posts: Observable<any>;

  constructor(public navCtrl: NavController, public http: Http) {
  }

  forwardRequest() {
    this.posts = this.http.get('http://68.230.95.141:8082/forward');
    this.posts
    .map(res => res.json())
    .subscribe(data => {
      console.log('my data: ', data);
    });
  }

  backRequest() {
    this.posts = this.http.get('http://68.230.95.141:8082/backward');
    this.posts
    .map(res => res.json())
    .subscribe(data => {
      console.log('my data: ', data);
    });
  }

  leftRequest() {
    this.posts = this.http.get('http://68.230.95.141:8082/turn-left');
    this.posts
    .map(res => res.json())
    .subscribe(data => {
      console.log('my data: ', data);
    });
  }

  rightRequest() {
    this.posts = this.http.get('http://68.230.95.141:8082/turn-right');
    this.posts
    .map(res => res.json())
    .subscribe(data => {
      console.log('my data: ', data);
    });
  }

  camUp() {
    this.posts = this.http.get('http://68.230.95.141:8082/camera-up');
    this.posts
    .map(res => res.json())
    .subscribe(data => {
      console.log('my data: ', data);
    });
  }

  camDown() {
    this.posts = this.http.get('http://68.230.95.141:8082/camera-down');
    this.posts
    .map(res => res.json())
    .subscribe(data => {
      console.log('my data: ', data);
    });
  }

  camLeft() {
    this.posts = this.http.get('http://68.230.95.141:8082/camera-left');
    this.posts
    .map(res => res.json())
    .subscribe(data => {
      console.log('my data: ', data);
    });
  }

  camRight() {
    this.posts = this.http.get('http://68.230.95.141:8082/camera-right');
    this.posts
    .map(res => res.json())
    .subscribe(data => {
      console.log('my data: ', data);
    });
  }

  camCenter() {
    this.posts = this.http.get('http://68.230.95.141:8082/camera-center');
    this.posts
    .map(res => res.json())
    .subscribe(data => {
      console.log('my data: ', data);
    });
  }

  robotRestart() {
    this.posts = this.http.get('http://68.230.95.141:8082/reboot');
    this.posts
    .map(res => res.json())
    .subscribe(data => {
      console.log('my data: ', data);
    });
  }

  ngAfterViewInit() {
    var canvas = <HTMLCanvasElement>document.getElementById('videoCanvas');
    let ctx: CanvasRenderingContext2D = canvas.getContext('2d');
    ctx.fillStyle = '#444';
    ctx.fillText('Loading...', canvas.width/2-30, canvas.height/3);
    var client = new WebSocket( 'ws://68.230.95.141:8084/' );
    var player = new jsmpeg(client, {canvas:canvas});
}

doRefresh(refresher) {
   console.log('Begin async operation', refresher);
   this.ngAfterViewInit();
   setTimeout(() => {
     console.log('Async operation has ended');
     refresher.complete();
   }, 2000);
 }
}
