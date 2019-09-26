include CssReset;

module Styles = {
  open Css;
  let title = style([textAlign(center)]);
};

ReactDOMRe.renderToElementWithId(
  <h1 className=Styles.title> "Todo app"->React.string </h1>,
  "root",
);
