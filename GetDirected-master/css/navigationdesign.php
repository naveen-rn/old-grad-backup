    <!-- Bootstrap core CSS -->
    <link href="../css/bootstrap.min.css" rel="stylesheet">

    <style>
      html, body, #map-canvas {
        background-color: #333;
        height: 93%;
        margin: 0px;
        padding: 0px
      }
      
      .controls {
        margin-top: 16px;
        border: 1px solid transparent;
        border-radius: 2px 0 0 2px;
        box-sizing: border-box;
        -moz-box-sizing: border-box;
        height: 32px;
        outline: none;
        box-shadow: 0 2px 6px rgba(0, 0, 0, 0.3);
      }
      
      #pac-input {
        background-color: #fff;
        padding: 0 11px 0 13px;
        width: 400px;
        font-family: Roboto;
        font-size: 15px;
        font-weight: 300;
        text-overflow: ellipsis;
      }

      #pac-input:focus {
        border-color: #4d90fe;
        margin-left: -1px;
        padding-left: 14px;  /* Regular padding-left + 1. */
        width: 401px;
      }

      .pac-container {
        font-family: Roboto;
      }

      #type-selector {
        color: #fff;
        background-color: #4d90fe;
        padding: 5px 11px 0px 11px;
      }

      #type-selector label {
        font-family: Roboto;
        font-size: 13px;
        font-weight: 300;
      }
      .cover-container {
        color: #fff;
        margin-right: auto;
        margin-left: auto;
      }

      .masthead-brand {
        color: #fff;
        margin-top: 10px;
        margin-bottom: 10px;
      }

     .masthead-nav > li {
      	display: inline-block;
     }
    
     .masthead-nav > li + li {
      	margin-left: 20px;
     }
    
     .masthead-nav > li > a {
     	padding-right: 0;
      	padding-left: 0;
      	font-size: 16px;
      	font-weight: bold;
      	color: #fff; /* IE8 proofing */
      	color: rgba(255,255,255,.75);
      	border-bottom: 2px solid transparent;
      }
    
     .masthead-nav > li > a:hover,
     .masthead-nav > li > a:focus {
     	background-color: transparent;
      	border-bottom-color: rgba(255,255,255,.25);
      }
    
     .masthead-nav > .active > a,
     .masthead-nav > .active > a:hover,
     .masthead-nav > .active > a:focus {
      	color: #fff;
      	border-bottom-color: #fff;
     }

     @media (min-width: 768px) {
      .masthead-brand {
        float: left;
      }
      .masthead-nav {
        float: right;
      }
    }

    /*
     * Affix and center
     */

    @media (min-width: 768px) {
      /* Pull out the header and footer */
      .masthead {
        position: fixed;
        top: 0;
      }
      .mastfoot {
        position: fixed;
        bottom: 0;
      }
      /* Start the vertical centering */
      .site-wrapper-inner {
        vertical-align: middle;
      }
      /* Handle the widths */
      .masthead,
      .mastfoot,
      .cover-container {
        width: 100%; /* Must be percentage or pixels for horizontal alignment */
      }
    }

    @media (min-width: 992px) {
      .masthead,
      .mastfoot,
      .cover-container {
        width: 700px;
      }
  }
</style>
