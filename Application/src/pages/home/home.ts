import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import * as jsmpeg from 'jsmpeg';
import { Http } from '@angular/http';
import 'rxjs/add/operator/map';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {

  posts: any;

  constructor(public navCtrl: NavController, public http: Http) {

    this.http.get('https://www.reddit.com/r/me_irl/top/.json?limit=10&sort=hot').map(res => res.json()).subscribe(data => {
      this.posts = data.data.children;
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
}
