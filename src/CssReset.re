open Css;

global(
  "html",
  [
    fontFamily("sans-serif"),
    padding(0->px),
    margin(0->px),
    backgroundColor("F4F7F8"->hex),
    display(flexBox),
    flexDirection(column),
  ],
);
global(
  "body",
  [
    margin2(~v=10->px, ~h=auto),
    backgroundColor("fff"->hex),
    color("46515B"->hex),
    borderRadius(10->px),
    padding(10->px),
    width(100.0->pct),
    maxWidth(600->px),
    boxShadows([
      Shadow.box(~y=5->px, ~blur=10->px, rgba(0, 0, 0, 0.1)),
      Shadow.box(~spread=1->px, rgba(0, 0, 0, 0.05)),
    ]),
  ],
);
